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

#include <goose/main/extension/generated_extension_loader.h>
#include <goose/main/extension_helper.h>
#include <goose-autocomplete/autocomplete_extension.h>

namespace goose {
    class CoreFunctionsExtension : public Extension {
    public:
        void Load(ExtensionLoader &db) override;

        std::string Name() override;

        std::string Version() const override;
    };

    class ParquetExtension : public Extension {
    public:
        void Load(ExtensionLoader &loader) override;

        std::string Name() override;

        std::string Version() const override;
    };


    class JsonExtension : public Extension {
    public:
        void Load(ExtensionLoader &loader) override;

        std::string Name() override;

        std::string Version() const override;
    };

    class IcuExtension : public Extension {
    public:
        void Load(ExtensionLoader &loader) override;

        std::string Name() override;

        std::string Version() const override;
    };


    //! Looks through the CMake-generated list of extensions that are linked into Goose currently to try load <extension>
    ExtensionLoadResult ExtensionHelper::LoadExtension(Goose &db, const std::string &extension) {
        if (extension == "core_functions") {
            db.LoadStaticExtension<CoreFunctionsExtension>();
            return ExtensionLoadResult::LOADED_EXTENSION;
        }
        if (extension == "parquet") {
            db.LoadStaticExtension<ParquetExtension>();
            return ExtensionLoadResult::LOADED_EXTENSION;
        }
        if (extension == "json") {
            db.LoadStaticExtension<JsonExtension>();
            return ExtensionLoadResult::LOADED_EXTENSION;
        }
        if (extension == "icu") {
            db.LoadStaticExtension<IcuExtension>();
            return ExtensionLoadResult::LOADED_EXTENSION;
        }
        if (extension == "autocomplete") {
            db.LoadStaticExtension<AutocompleteExtension>();
            return ExtensionLoadResult::LOADED_EXTENSION;
        }

        return ExtensionLoadResult::NOT_LOADED;
    }

    vector<string> LinkedExtensions() {
        vector<string> VEC = {
            "core_functions",
            "parquet",
            "json",
            "icu",
            "autocomplete"
        };
        return VEC;
    }

    void ExtensionHelper::LoadAllExtensions(Goose &db) {
        for (auto &ext_name: LinkedExtensions()) {
            LoadExtension(db, ext_name);
        }
    }

    vector<string> ExtensionHelper::LoadedExtensionTestPaths() {
        vector<string> VEC = {
        };
        return VEC;
    }
}
