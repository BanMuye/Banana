//
// Created by cyzho on 2025/10/10.
//

#ifndef SCENEHIERACHYPANEL_H
#define SCENEHIERACHYPANEL_H
#include "Banana/Core/Core.h"
#include "Banana/Scene/Entity.h"
#include "Banana/Scene/Scene.h"


namespace Banana {
    class SceneHierarchyPanel {
    public:
        SceneHierarchyPanel() = default;

        SceneHierarchyPanel(const Ref<Scene> &scene);

        ~SceneHierarchyPanel() = default;

        void SetContext(const Ref<Scene> &scene);

        void OnImGuiRender();

    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);

    private:
        Ref<Scene> m_Context;
        Entity m_SelectionContext;
    };
}


#endif //SCENEHIERACHYPANEL_H
