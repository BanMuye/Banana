//
// Created by cyzho on 2025/10/21.
//

#ifndef CONTENTBROWERPANEL_H
#define CONTENTBROWERPANEL_H
#include <filesystem>


namespace Banana {
    class ContentBrowserPanel {
    public:
        ContentBrowserPanel();

        void OnImGuiRender();

    private:
        std::filesystem::path m_CurrentDirectory;
    };
}


#endif //CONTENTBROWERPANEL_H
