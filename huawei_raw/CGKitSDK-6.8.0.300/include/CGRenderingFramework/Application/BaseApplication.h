/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Overview of the Application. Defining the application using steps.
 * contains initialization, update, render etc.
 */

#ifndef BASE_APPLICATION_H
#define BASE_APPLICATION_H

#include "Core/Types.h"
#include "Rendering/Graphics/GraphicsRenderer.h"
#include "Scene/SceneManager.h"

NS_CG_BEGIN

class InputEvent;
class Platform;
class ScreenShot;

class CGKIT_EXPORT BaseApplication {
public:
    BaseApplication();
    virtual ~BaseApplication();
    BaseApplication operator=(const BaseApplication& baseApplication) = delete;
    BaseApplication(const BaseApplication& baseApplication) = delete;

    /*
     * Starts the BaseApplication and initializes the log system.
     * If the Android platform is used, param can be converted to type android_app
     * to complete the android_app binding of the file system
     * and event callback system startup of the Android platform.
     */
    virtual void Start(void* param);

    /*
     * Initializes the app including the resource system, rendering system, and scene manager system.
     */
    virtual void Initialize(const void* winHandle, u32 width, u32 height);

    /*
     * Uninitializes resources when an app exits
     * including the resource system, rendering system, scene manager system, and log system.
     */
    virtual void Uninitialize();

    /*
     * Rebuilds resources including the rendering system, resource manager system,
     * and scene manager system when the app is switched from the background to the foreground.
     */
    virtual bool Resume(const void* winHandle, u32 width, u32 height);

    /*
     * Destroys resources including the rendering system, resource manager system,
     * and scene manager system when the app is switched from the foreground to the background.
     */
    virtual void Pause();

    /*
     * Initializes the scene system.
     */
    virtual void InitScene();

    /*
     * Updates the scene system, scene objects, and object components.
     */
    virtual void Update(f32 deltaTime);

    /*
     * Collects the object rendering list and performs the rendering tasks.
     */
    virtual void Render();

    /*
     * Changes the window size and starts the Resize process of SceneManager.
     */
    virtual void Resize(u32 width, u32 height);

    /*
     * The main loop that completes clock timing, controls the number of updated frames,
     * and calls the Update and Render functions.
     */
    virtual void Run();

    /*
     * Distributes and processes keyboard and touch events.
     */
    virtual void ProcessInputEvent(const InputEvent* inputEvent);

    /*
     * The main loop of the Android platform that processes events.
     * If the app is currently focused, it calls the Run function.
     */
    void MainLoop();

    /*
     * Gives focus to the app.
     */
    void SetFocus(bool flag);

    /*
     * Returns true if the app is currently focused. If not, the Update function is not called.
     */
    bool IsFocused() const;

    /*
     * Get the snapshot's pixel data.
     */
    const u8* GetSnapshotData() const;

    /*
     * Save the snapshot's pixel data to fileName.
     */
    void SaveSnapshotToFile(const String& fileName);

    const GraphicsRenderer* GetGraphicsRenderer() const
    {
        return m_graphicsRenderer;
    }

    const SceneManager* GetSceneManager() const
    {
        return m_sceneManager;
    }

    ResourceManager* GetResourceManager() const
    {
        return m_sceneManager->GetResourceManager();
    }

    /*
    * Obtains the engine name.
    */
    const c8* GetEngineName() const;

    /*
    * Obtains the title.
    */
    const c8* GetTitle() const;

    /*
    * Set full screen enable.
    */
    void EnableFullScreen(bool enable);

    bool IsFullScreen() const;

    /*
    * Set the screen width and height.
    */
    void SetWindowSize(u32 width, u32 height);

    /*
     * Obtains the aspect ratio of the screen.
     */
    f32 GetAspectRatio() const;

    /*
     * Obtains the screen width.
     */
    u32 GetScreenWidth() const;

    /*
     * Obtains the screen height.
     */
    u32 GetScreenHeight() const;

    /*
     * Returns true if CG Kit supports the current platform.
     * Currently, only devices running Android 8.0 or later are supported.
     */
    bool IsPlatformSupported() const;

    /*
     * Obtains the project directory.
     */
    String GetProgramDirectory() const;

    /*
     * Enables multithreaded rendering which is designed for heavy CPU load scenes,
     * especially where the model count exceeds 5000.
     */
    bool EnableMultiThreadRendering(bool open);

    /*
     * (Optional) Sets the thread count before enabling multithreaded rendering.
     * The value range is [2, CPU core count]. The default value is half of the CPU core count - 1.
     */
    u32 SetThreadCount(u32 count);

    /*
     * Set the scene manager type. The default value is the quadtree scene manager.
     */
    void SetSceneManagerType(SceneManagerType sceneManagerType);

    /*
     * Set rendering sort type. The default is sort by distance.
     */
    void SetRenderingSortType(RenderingSortType sortType);

    /*
     * Enables Frustum Cull.
     */
    void EnableFrustumCull(bool enable);

    u32 GetCascadeSplitCount() const;
    u32 GetBackBufferCount() const;

protected:
    virtual void HandleKeyboardEvent(const InputEvent* inputEvent);
    virtual void HandleTouchEvent(const InputEvent* inputEvent);

    f32 GetFps() const;
    void EnableValidationLayer(bool enable);
    void EnableApiDumpLayer(bool enable);
    void EnableMultiThreadFrustumCulling(bool enable);

protected:
    Platform* m_platform = nullptr;
    GraphicsRenderer* m_graphicsRenderer = nullptr;
    SceneManager* m_sceneManager = nullptr;
    f32 m_fps = 0;
    f32 m_frameTimeFPS = 0;
    u32 m_frameCountFPS = 0;
    bool m_focus = true;
    bool m_hasInit = false;

    void InitSceneManager();

private:
    ScreenShot* m_screenShot = nullptr;
    GraphicsConfig* m_graphicsConfig = nullptr;
};

NS_CG_END

#endif
