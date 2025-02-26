#ifndef FTXUI_WRAPPER_H
#define FTXUI_WRAPPER_H

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <optional>
#include <string>
#include <vector>
#include <utility>

class FtxuiWrapper
{
public:
    FtxuiWrapper(int width = 60, int height = 20);

    void showMessageBox(const std::string &message,
                        const std::string &title = "Message") const {
        auto screen = ftxui::ScreenInteractive::TerminalOutput();
        auto ok_button = ftxui::Button("OK", [&] { screen.ExitLoopClosure()(); });
        auto container = ftxui::Container::Vertical({ok_button});
        auto renderer = ftxui::Renderer(container, [&] {
            using namespace ftxui;
            return vbox({
                       text(title) | bold | center,
                       separator(),
                       text(message) | center,
                       separator(),
                       hbox({filler(), ok_button->Render(), filler()})
                   }) |
                   border | size(HEIGHT, EQUAL, dialogHeight) |
                   size(WIDTH, EQUAL, dialogWidth) | center;
        });
        screen.Loop(renderer);
    }

    bool showYesNoDialog(const std::string &question,
                         const std::string &title = "Confirm") const {
        auto screen = ftxui::ScreenInteractive::TerminalOutput();
        bool result = false;
        auto yes_button = ftxui::Button("Yes", [&] {
            result = true;
            screen.ExitLoopClosure()();
        });
        auto no_button = ftxui::Button("No", [&] {
            result = false;
            screen.ExitLoopClosure()();
        });
        auto container = ftxui::Container::Horizontal({yes_button, no_button});
        auto renderer = ftxui::Renderer(container, [&] {
            using namespace ftxui;
            return vbox({
                       text(title) | bold | center,
                       separator(),
                       text(question) | center,
                       separator(),
                       hbox({filler(), yes_button->Render(), text("  "),
                             no_button->Render(), filler()})
                   }) |
                   border | size(HEIGHT, EQUAL, dialogHeight) |
                   size(WIDTH, EQUAL, dialogWidth) | center;
        });
        screen.Loop(renderer);
        return result;
    }

    std::optional<std::string> showInputDialog(const std::string &prompt,
                                               const std::string &defaultValue = "",
                                               const std::string &title = "Input") const {
        auto screen = ftxui::ScreenInteractive::TerminalOutput();
        std::string input = defaultValue;
        auto input_component = ftxui::Input(&input, "Enter text...");
        auto ok_button = ftxui::Button("OK", [&] { screen.ExitLoopClosure()(); });
        auto container = ftxui::Container::Vertical({input_component, ok_button});
        auto renderer = ftxui::Renderer(container, [&] {
            using namespace ftxui;
            return vbox({
                       text(title) | bold | center,
                       separator(),
                       text(prompt) | center,
                       input_component->Render() | center,
                       separator(),
                       hbox({filler(), ok_button->Render(), filler()})
                   }) |
                   border | size(HEIGHT, EQUAL, dialogHeight) |
                   size(WIDTH, EQUAL, dialogWidth) | center;
        });
        screen.Loop(renderer);
        return input.empty() ? std::nullopt : std::optional<std::string>{input};
    }

    std::optional<std::string> showMenu(
        const std::string &prompt,
        const std::vector<std::pair<std::string, std::string>> &options,
        const std::string &title = "Menu") const {
        auto screen = ftxui::ScreenInteractive::TerminalOutput();
        std::vector<std::string> items;
        std::vector<std::string> keys;
        for (const auto &[key, desc] : options) {
            items.push_back(key + " - " + desc);
            keys.push_back(key);
        }
        int selected = 0;
        auto menu = ftxui::Menu(&items, &selected);
        auto ok_button = ftxui::Button("OK", [&] { screen.ExitLoopClosure()(); });
        auto container = ftxui::Container::Vertical({menu, ok_button});
        auto renderer = ftxui::Renderer(container, [&] {
            using namespace ftxui;
            return vbox({
                       text(title) | bold | center,
                       separator(),
                       text(prompt) | center,
                       separator(),
                       menu->Render() | border,
                       separator(),
                       hbox({filler(), ok_button->Render(), filler()})
                   }) |
                   border | size(HEIGHT, EQUAL, dialogHeight) |
                   size(WIDTH, EQUAL, dialogWidth) | center;
        });
        screen.Loop(renderer);
        if (items.empty())
            return std::nullopt;
        return keys[selected];
    }

    std::vector<std::string> showChecklist(
        const std::string &prompt,
        const std::vector<std::pair<std::string, bool>> &options,
        const std::string &title = "Checklist") const {

        auto screen = ftxui::ScreenInteractive::TerminalOutput();
        std::vector<std::string> keys;
        std::vector<std::shared_ptr<bool>> selections;
        std::vector<ftxui::Component> checkbox_components;

        for (const auto &[key, init] : options) {
            keys.push_back(key);
            selections.push_back(std::make_shared<bool>(init));  // Use shared_ptr<bool> instead of vector<bool>

            auto checkbox = ftxui::Checkbox(key, selections.back().get()); // Correct Checkbox usage
            checkbox_components.push_back(checkbox);
        }

        auto ok_button = ftxui::Button("OK", [&] {  });

        auto container = ftxui::Container::Vertical(checkbox_components);
        container->Add(ok_button);

        auto renderer = ftxui::Renderer(container, [&] {
            using namespace ftxui;
            std::vector<ftxui::Element> elems;

            elems.push_back(text(title) | bold | center);
            elems.push_back(separator());
            elems.push_back(text(prompt) | center);

            for (auto &checkbox : checkbox_components) {
                elems.push_back(checkbox->Render());
            }

            elems.push_back(separator());
            elems.push_back(hbox({filler(), ok_button->Render(), filler()}));

            return vbox(elems) | border | size(HEIGHT, EQUAL, dialogHeight) |
                   size(WIDTH, EQUAL, dialogWidth) | center;
        });

        screen.Loop(renderer);

        std::vector<std::string> result;
        for (size_t i = 0; i < selections.size(); ++i) {
            if (*selections[i]) {
                result.push_back(keys[i]);
            }
        }

        return result;
    }






private:
    int dialogWidth;
    int dialogHeight;
};

inline FtxuiWrapper::FtxuiWrapper(int width, int height)
    : dialogWidth(width), dialogHeight(height) {}

#endif // FTXUI_WRAPPER_H
