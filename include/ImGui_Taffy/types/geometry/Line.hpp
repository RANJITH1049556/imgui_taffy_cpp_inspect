#pragma once

#include <taffy/geometry/Line.hpp>

#include <imgui.h>

#include <ImGui_Taffy/utils/TypeDescription.hpp>

#include <ImGui_Taffy/show_descriptions.hpp>
#include <ImGui_Taffy/utils/HelpMarker.hpp>
#include <ImGui_Taffy/utils/description.hpp>

namespace ImGui_Taffy {

template <typename T>
inline bool edit_Line_T(
    taffy::Line<T>& value,
    bool (*edit_field_func) (T& field),

    const TypeDescription& type_description = TypeDescription::Default()
)
{
    const bool show_descriptions = is_show_descriptions();

    bool modified = false;

    ImGui::PushID(&value);
    {
        constexpr ImGuiTableFlags TABLE_FLAGS =
            ImGuiTableFlags_Resizable      |
            ImGuiTableFlags_BordersInnerV  |
          //ImGuiTableFlags_SizingFixedFit |
            ImGuiTableFlags_NoSavedSettings;
        constexpr char TABLE_ID[] = "taffy_line_table";

        const ImVec2 table_size =
            show_descriptions ?
                ImVec2{ ImGui::GetContentRegionAvail().x-30.0f, 0.0f } // Extra offset for `HelpMarker`
            :
                ImVec2{ 0.0f, 0.0f };

        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS, table_size) )
        {
            // Table columns specification, needed to set 'fixed' & 'stretch' flags
            ImGui::TableSetupColumn("Name",  ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthStretch);
            //ImGui::TableHeadersRow(); // <-- commented to not show table header

            // -----------------------------------------------------------------

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("start");

            if(show_descriptions)
            {
                ImGui::SameLine();
                HelpMarker(false, [] {
                    ImGui::TextUnformatted("The start position of a line");
                });
            }

            ImGui::TableNextColumn();
            if( edit_field_func(value.start) ) {
                modified = true;
            }

            // -----------------------------------------------------------------

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("end");

            if(show_descriptions)
            {
                ImGui::SameLine();
                HelpMarker(false, [] {
                    ImGui::TextUnformatted("The end position of a line");
                });
            }

            ImGui::TableNextColumn();
            if( edit_field_func(value.end) ) {
                modified = true;
            }

            // -----------------------------------------------------------------

            ImGui::EndTable();
        }

        if(show_descriptions)
        {
            static const TypeDescription DEFAULT_TYPE_DESCRIPTION {
                "Line<T>",
                [] {
                    ImGui::TextUnformatted("An abstract \"line\". Represents any type that has a start and an end");
                },
                false
            };
            
            const auto description = description_or_default(type_description, DEFAULT_TYPE_DESCRIPTION);

            ImGui::SameLine();
            HelpMarker(description.type_description_interactive, [description]
            {
                description::TypeName(description.type_name);
                ImGui::NewLine();
                description.type_description_fn();
            });
        }
    }
    ImGui::PopID();

    return modified;
}

} // namespace ImGui_Taffy
