#include "stdafx.h"
#include "Resource.h"
#include "Scene.h"

//////////////////////////////////////////////////////////////////////////

using namespace CommonLibOgl;
using namespace CommonLibOglTestApp;

//////////////////////////////////////////////////////////////////////////


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Redirect output from std::wcout and std::wcerr to the log file.
    std::wofstream out("log.txt");
    std::wcout.rdbuf(out.rdbuf());
    std::wcerr.rdbuf(out.rdbuf());

    int res = 1;

    try
    {
        // Width and height of the window client area.
        const int ClientWidth  = 800;
        const int ClientHeight = 600;

        //WindowInfo(int clientWidth, int clientHeight, UINT titleId, UINT wndClassId, WORD iconId, WORD iconSmallId, WORD menuId = 0)

        // Window title ID, class ID, icon ID and menu ID were copied from the Visual Studio-generated window code.
        WindowInfo wndInfo(ClientWidth, ClientHeight, IDS_APP_TITLE, IDC_COMMONLIBOGLTEST,
            IDI_COMMONLIBOGLTEST, IDI_SMALL, IDC_COMMONLIBOGLTEST);

        const int OpenGLVersionMajor = 4;
        const int OpenGLVersionMinor = 4;

        // Field of view angle.
        const GLfloat FieldOfView = 45.0f;

        // Frustum boundaries.
        const GLfloat FrustumNear = 0.1f;
        const GLfloat FrustumFar  = 1000.0f;

        OpenGLInfo openGLInfo(OpenGLVersionMajor, OpenGLVersionMinor, FieldOfView, FrustumNear, FrustumFar);

        // TODO: populate the scene.
        std::shared_ptr<Scene> spScene = std::make_shared<Scene>();

        // TODO: uncomment
#if 0
        WindowMain mainWindow(hInstance, wndInfo, openGLInfo, spScene);
        //WindowMain(HINSTANCE hInstance, const WindowInfo& wndInfo, const OpenGLInfo& openGLInfo, std::weak_ptr<OglScene>& scene);
#endif

        // TODO: create shaders
        const ShaderCollection shaders = {
            { GL_VERTEX_SHADER,   "shaders\\terrain.vert" },
            { GL_FRAGMENT_SHADER, "shaders\\terrain.frag" }
        };

        // TODO: uncomment
#if 0
        res = mainWindow.runMessageLoop(nCmdShow, shaders);
#endif
    }
    catch (const Exception& ex)
    {
        std::wcerr << ex.message() << '\n';
        return 1;
    }
    catch (const std::bad_alloc&)
    {
        std::wcerr << L"Memalloc failure\n";
        return 1;
    }
    catch (...)
    {
        std::wcerr << L"Unknown exception\n";
        return 1;
    }

    return res;
}
