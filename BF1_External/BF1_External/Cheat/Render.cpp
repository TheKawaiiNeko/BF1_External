#include "Cheat.h"

Player local, *pLocal = &local;
const char* KeyNames[];

// Info
void Cheat::RenderInfo()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)g.GameSize.right, (float)g.GameSize.bottom));
    ImGui::Begin("##Info", (bool*)NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs);

    ImGui::Text("BF1 External [%.1f FPS]", ImGui::GetIO().Framerate);

    ImGui::End();
}

// Menu
void Cheat::RenderMenu()
{
    ImGui::SetNextWindowSize(ImVec2(775.f, 520.f));
    ImGui::Begin("// Removed", (bool*)NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    //---// Clild 0 //-----------------------------------//
    ImGui::BeginChild("##BaseChild", ImVec2(150.f, ImGui::GetContentRegionAvail().y), false);
    ImGui::BeginChild("##TitleChild", ImVec2(ImGui::GetContentRegionAvail().x, 150.f), true);

    ImGui::Text("// Removed");

    ImGui::EndChild();

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::BeginChild("##SomeChild", ImVec2(ImGui::GetContentRegionAvail()), true);

    ImGui::InputText("ID", LocalName, IM_ARRAYSIZE(LocalName));

    // Exit
    ImGui::SetCursorPosY(ImGui::GetContentRegionAvail().y - 10.f);
    ImGui::Separator();
    if (ImGui::Button("Exit", ImVec2(135.f, 30.f)))
        g.Run = false;

    ImGui::EndChild();
    ImGui::EndChild();
    //---// Clild 0 //-----------------------------------//

    ImGui::SameLine();

    //---// Clild 1 //-----------------------------------//
    ImGui::BeginChild("BaseChild##2", ImVec2(ImGui::GetContentRegionAvail()));

    ImGuiStyle& style = ImGui::GetStyle();
    auto FramePadding = style.FramePadding;
    style.FramePadding = ImVec2(30, 8);

    if (ImGui::BeginTabBar("##ContextTabBar"))
    {
        style.FramePadding = ImVec2(30, 8);
        if (ImGui::BeginTabItem("   AimBot   "))
        {
            /*---------------*/
            style.FramePadding = FramePadding;
            ImGui::Spacing();
            ImGui::BeginChild("##LeftAimBase", ImVec2(ImGui::GetContentRegionAvail().x / 2.f - 8.f, ImGui::GetContentRegionAvail().y), false);

            ImGui::Text("// Removed");

            ImGui::EndChild();
            /*---------------*/
            ImGui::SameLine();
            /*---------------*/
            ImGui::BeginChild("##RightAimBase", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false);

            ImGui::Text("// Removed");

            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::NewLine();

            // KeyBinder - サンプルとして残しておきます。
            ImGui::Text("  KeyBind");
            ImGui::Separator();
            ImGui::Spacing();

            const char* text1 = KeyNames[g.AimKey0];
            const char* text2 = KeyNames[g.AimKey1];

            if (g.KeyBinding)
            {
                switch (g.BindID)
                {
                case 1:
                    text1 = "< Press Any Key >";
                    break;
                case 2:
                    text2 = "< Press Any Key >";
                    break;
                default:
                    break;
                }
            }

            ImGui::Text("1st :");
            if (ImGui::Button(text1, ImVec2(215.f, 20.f)))
            {
                g.KeyBinding = true;
                g.BindID = 1;
                std::thread([&]() {this->KeyBinder(g.AimKey0); }).detach();
            }

            ImGui::Text("2nd :");
            if (ImGui::Button(text2, ImVec2(215.f, 20.f)))
            {
                g.KeyBinding = true;
                g.BindID = 2;
                std::thread([&]() {this->KeyBinder(g.AimKey1); }).detach();
            }
   
            ImGui::EndChild();
            /*---------------*/

            ImGui::EndTabItem();
        }

        style.FramePadding = ImVec2(30, 8);
        if (ImGui::BeginTabItem("   Visual   "))
        {
            /*---------------*/
            style.FramePadding = FramePadding;
            ImGui::Spacing();
            ImGui::BeginChild("##LeftVisualBase", ImVec2(ImGui::GetContentRegionAvail().x / 2.f - 8.f, ImGui::GetContentRegionAvail().y), false);

            ImGui::Text("  Visual");
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::Checkbox("ESP", &g.ESP);

            ImGui::NewLine();
            ImGui::Spacing();

            ImGui::Text("  ESP Options");
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::Checkbox("Box", &g.ESP_Box);
            ImGui::Checkbox("Line", &g.ESP_Line);
            ImGui::Checkbox("Distance", &g.ESP_Distance);
            ImGui::Checkbox("HealthBar", &g.ESP_HealthBar);

            ImGui::EndChild();
            /*---------------*/
            ImGui::SameLine();
            /*---------------*/
            ImGui::BeginChild("##RightVisualBase", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false);

            ImGui::Text("  ESP Setting");
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::SliderFloat("Distance", &g.ESP_MaxDistance, 50.f, 2000.f);

            ImGui::NewLine();
            ImGui::Spacing();

            ImGui::Text("  ESP Colors");
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::ColorEdit4("Normal ", &Col_ESP_Normal.Value.x);
            ImGui::ColorEdit4("Visible", &Col_ESP_Visible.Value.x);
            ImGui::ColorEdit4("Team", &Col_ESP_Team.Value.x);

            ImGui::EndChild();
            /*---------------*/

            ImGui::EndTabItem();
        }

        style.FramePadding = ImVec2(30, 8);
        if (ImGui::BeginTabItem("    Misc    "))
        {
            /*---------------*/
            style.FramePadding = FramePadding;
            ImGui::Spacing();
            ImGui::BeginChild("##LeftMiscBase", ImVec2(ImGui::GetContentRegionAvail().x / 2.f - 8.f, ImGui::GetContentRegionAvail().y), false);

            ImGui::Text("// Removed");

            ImGui::EndChild();
            /*---------------*/
            ImGui::SameLine();
            /*---------------*/
            ImGui::BeginChild("##RightMiscBase", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false);

            ImGui::Text("// Removed");

            ImGui::EndChild();
            /*---------------*/

            ImGui::EndTabItem();
        }

        style.FramePadding = ImVec2(30, 8);
        if (ImGui::BeginTabItem("  Developer  "))
        {
            /*---------------*/
            style.FramePadding = FramePadding;
            ImGui::Spacing();
            ImGui::BeginChild("##LeftDevBase", ImVec2(ImGui::GetContentRegionAvail().x / 2.f - 8.f, ImGui::GetContentRegionAvail().y), false);

            ImGui::Text("// Removed");

            ImGui::EndChild();
            /*---------------*/
            ImGui::SameLine();
            /*---------------*/
            ImGui::BeginChild("##RightDevBase", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false);

            ImGui::Text("// Removed");

            ImGui::EndChild();
            /*---------------*/

            ImGui::EndTabItem();
        }

        style.FramePadding = FramePadding;
        ImGui::EndTabBar();
    }

    ImGui::EndChild();
    //---// Clild 1 //-----------------------------------//

    ImGui::End();
}

// ESP
void Cheat::RenderESP()
{
    // ImGui Window
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)g.GameSize.right, (float)g.GameSize.bottom));
    ImGui::Begin("##ESP", (bool*)NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs);

    for (int i = 0; i < 70; i++)
    {
        Player ent, *pEntity = &ent;
        pEntity->GetPlayer(i);

        if (!pEntity->IsValid())
            continue;
        else if (pLocal->IsValid() && pEntity->ClientPlayer == pLocal->ClientPlayer)
            continue;

        pEntity->Update();

        char name[128];
        ReadProcessMemory(m.pHandle, (void*)(pEntity->ClientPlayer + offset::PlayerName), &name, sizeof(name), nullptr);
        
        if (strcmp(name, LocalName) == 0)
        {
            local = ent;
            continue;
        }

        if (pEntity->IsDead())
            continue;
        else if (pEntity->Team == pLocal->Team)
            continue;
        else if (pEntity->InVehicle())
            continue;

        // Get Distance
        float distance = GetDistance(pLocal->Position, pEntity->Position);

        if (distance > g.ESP_MaxDistance)
            continue;

        // WorldToScreen
        Vector2 ScreenPosition = Vector2(0.f, 0.f);
        if (!WorldToScreen(pEntity->Position, ScreenPosition))
            continue;

        if (ScreenPosition != Vector2(0.f, 0.f))
        {
            ImColor color = pEntity->IsVisible() ? Col_ESP_Visible : Col_ESP_Normal;

            // Box and more用
            Vector3 BoxTop = pEntity->Position + pEntity->GetAABB().Max;
            Vector3 BoxBottom = pEntity->Position + pEntity->GetAABB().Min;
            Vector2 vTop, vBtm;
            if (!WorldToScreen(BoxTop, vTop) || !WorldToScreen(BoxBottom, vBtm))
                continue;

            float Height = vBtm.y - vTop.y;
            float Width = Height / 2.f;

            // Box
            if (g.ESP_Box)
            {
                DrawLine(ImVec2(ScreenPosition.x + (Width / 2.f), vTop.y), ImVec2(ScreenPosition.x - (Width / 2.f), vTop.y), color, 1.f);
                DrawLine(ImVec2(ScreenPosition.x + (Width / 2.f), ScreenPosition.y), ImVec2(ScreenPosition.x - (Width / 2.f), ScreenPosition.y), color, 1.f);
                DrawLine(ImVec2(ScreenPosition.x + (Width / 2.f), vTop.y), ImVec2(ScreenPosition.x + (Width / 2.f), ScreenPosition.y), color, 1.f);
                DrawLine(ImVec2(ScreenPosition.x - (Width / 2.f), vTop.y), ImVec2(ScreenPosition.x - (Width / 2.f), ScreenPosition.y), color, 1.f);
            }

            // Line
            if (g.ESP_Line)
                DrawLine(ImVec2(g.GameSize.right / 2.f, g.GameSize.bottom), ImVec2(ScreenPosition.x, ScreenPosition.y), color, 1.f);

            // Healthbar
            HealthBar(ScreenPosition.x - (Width / 2.f) - 4, ScreenPosition.y, 2.f, -Height, pEntity->Health, 100.f);

            std::string vContext;

            // Distance
            if (g.ESP_Distance)
                vContext = std::to_string((int)distance) + "m";

            // Name
            if (g.ESP_Name)
                vContext = vContext + "|" + name;

            // Distance or Name is enable
            if (!vContext.empty())
            {
                ImVec2 textSize = ImGui::CalcTextSize(vContext.c_str());
                float TextCentor = textSize.x / 2.f;
                String(ImVec2(ScreenPosition.x - TextCentor, ScreenPosition.y), ImColor(1.f, 1.f, 1.f, 1.f), vContext.c_str());
            }
        }
    }

    ImGui::End();
}

const char* KeyNames[] =
{
    "None",
    "Mouse Left",
    "Mouse Right",
    "Cancel",
    "Middle Center",
    "MouseSide1",
    "MouseSide2",
    "",
    "Backspace",
    "Tab",
    "",
    "",
    "Clear",
    "Enter",
    "",
    "",
    "Shift",
    "Ctrl",
    "Alt",
    "Pause",
    "CapsLock",
    "",
    "",
    "",
    "",
    "",
    "",
    "Escape",
    "",
    "",
    "",
    "",
    "Space",
    "Page Up",
    "Page Down",
    "End",
    "Home",
    "Left",
    "Up",
    "Right",
    "Down",
    "",
    "",
    "",
    "Print",
    "Insert",
    "Delete",
    "",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "",
    "",
    "",
    "",
    "",
    "Numpad 0",
    "Numpad 1",
    "Numpad 2",
    "Numpad 3",
    "Numpad 4",
    "Numpad 5",
    "Numpad 6",
    "Numpad 7",
    "Numpad 8",
    "Numpad 9",
    "Multiply",
    "Add",
    "",
    "Subtract",
    "Decimal",
    "Divide",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
};
