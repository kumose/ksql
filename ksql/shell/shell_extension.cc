// Copyright (C) Kumo inc. and its affiliates.
// Author: Jeff.li lijippy@163.com
// All rights reserved.
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//


#include <ksql/shell/shell_extension.h>
#include <goose/main/extension/extension_loader.h>
#include <goose/common/vector_operations/unary_executor.h>
#include <goose/main/config.h>
#include <ksql/shell/shell_state.h>
#include <goose/parser/tableref/column_data_ref.h>
#include <ksql/shell/shell_renderer.h>
#include <stdio.h>
#include <stdlib.h>

namespace goose {
    static void GetEnvFunction(DataChunk &args, ExpressionState &state, Vector &result) {
        UnaryExecutor::Execute<string_t, string_t>(args.data[0], result, args.size(), [&](string_t input) {
            string env_name = input.GetString();
            auto env_value = getenv(env_name.c_str());
            if (!env_value) {
                return StringVector::AddString(result, string());
            }
            return StringVector::AddString(result, env_value);
        });
    }

    static unique_ptr<FunctionData> GetEnvBind(ClientContext &context, ScalarFunction &bound_function,
                                               vector<unique_ptr<Expression> > &arguments) {
        auto &config = DBConfig::GetConfig(context);
        if (!config.options.enable_external_access) {
            throw PermissionException("getenv is disabled through configuration");
        }
        return nullptr;
    }

    unique_ptr<TableRef> ShellScanLastResult(ClientContext &context, ReplacementScanInput &input,
                                             optional_ptr<ReplacementScanData> data) {
        auto &table_name = input.table_name;
        if (table_name != "_") {
            return nullptr;
        }
        auto &state = goose_shell::ShellState::Get();
        if (!state.last_result) {
            throw BinderException("Failed to query last result \"_\": no result available");
        }
        return make_uniq<ColumnDataRef>(state.last_result->Collection(), state.last_result->names);
    }

    void ShellExtension::Load(ExtensionLoader &loader) {
        loader.SetDescription("Adds CLI-specific support and functionalities");
        loader.RegisterFunction(
            ScalarFunction("getenv", {LogicalType::VARCHAR}, LogicalType::VARCHAR, GetEnvFunction, GetEnvBind));

        auto &config = goose::DBConfig::GetConfig(loader.GetDatabaseInstance());
        config.replacement_scans.push_back(goose::ReplacementScan(goose::ShellScanLastResult));
    }

    std::string ShellExtension::Name() {
        return "shell";
    }

    std::string ShellExtension::Version() const {
        return DefaultVersion();
    }
} // namespace goose
