#
# Copyright 2024 Kumo.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
###########################################################################
# below are examples, after initialization, modify it to your own.
###########################################################################
###kmcmake_example
set(LN_SRC
        linenoise/highlighting.cc
        linenoise/history.cc
        linenoise/linenoise.cc
        linenoise/linenoise-c.cc
        linenoise/rendering.cc
        linenoise/terminal.cc
)
kmcmake_cc_library(
        NAMESPACE ${PROJECT_NAME}
        NAME linenoise
        SOURCES
        ${LN_SRC}
        CXXOPTS
        ${KMCMAKE_CXX_OPTIONS}
        PLINKS
        ${KMCMAKE_DEPS_LINK}
)

set(SH_SRC
        shell/shell_command_line_option.cc
        shell/shell_extension.cc
        shell/shell_helpers.cc
        shell/shell_highlight.cc
        shell/shell_metadata_command.cc
        shell/shell_progress_bar.cc
        shell/shell_prompt.cc
        shell/shell_renderer.cc
        shell/shell_render_table_metadata.cc
        shell/shell_windows.cc
)
kmcmake_cc_library(
        NAMESPACE ${PROJECT_NAME}
        NAME shell
        SOURCES
        ${SH_SRC}
        CXXOPTS
        ${KMCMAKE_CXX_OPTIONS}
        PLINKS
        ${KMCMAKE_DEPS_LINK}
)


kmcmake_cc_interface(
        NAMESPACE ${PROJECT_NAME}
        NAME api
        HEADERS
        api.h
        CXXOPTS
        ${KMCMAKE_CXX_OPTIONS}
        PUBLIC
)

kmcmake_cc_binary(
        NAMESPACE ${PROJECT_NAME}
        NAME ksql
        SOURCES
        shell.cc
        extention_loader.cc
        CXXOPTS
        ${KMCMAKE_CXX_OPTIONS}
        LINKS
        ${PROJECT_NAME}::linenoise_static
        ${PROJECT_NAME}::shell_static
        ${KMCMAKE_DEPS_LINK}
        PUBLIC
)


###kmcmake_example