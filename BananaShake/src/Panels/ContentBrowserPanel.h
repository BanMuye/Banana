//
// Created by cyzho on 2025/10/21.
//

#ifndef CONTENTBROWERPANEL_H
#define CONTENTBROWERPANEL_H
#include <filesystem>

#include "Banana/Core/Core.h"
#include "Banana/Renderer/Texture.h"


namespace Banana {
    class ContentBrowserPanel {
    public:
        ContentBrowserPanel();

        void OnImGuiRender();

    private:
        std::filesystem::path m_CurrentDirectory;

        Ref<Texture2D> m_DirectoryIcon;
        Ref<Texture2D> m_FileIcon;
    };
}


#endif //CONTENTBROWERPANEL_H
