#include<Windows.h>   //用于做窗口程序
#include<time.h>

//地图
int g_arrBackground[20][10] = { 0 };

//俄罗斯方块
int g_arrElsfk[2][4] = { 0 };

//窗口处理函数声明
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//窗口绘图函数声明
void OnPaint(HDC hDC);
//绘制方块声明
void DrawBlock(HDC hDC);
//随机生成俄罗斯方块声明
void CreateTrtrisBlock();

//main:黑窗口入口程序 
//WinMain:窗口程序的入口函数 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//做一个窗口

	//1、设计窗口类（设计一个窗口的类型） 
	TCHAR szAppClassName[] = TEXT("DunkaiEDU");

	WNDCLASS wc = { 0 };
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255)); //软件的背景颜色设置
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);		   //加载光标
	wc.lpfnWndProc   = WindowProc;					       //窗口处理函数
	wc.hInstance     = hInstance;						   //当前应用程序实例句柄
	wc.style         = CS_HREDRAW | CS_VREDRAW;            //窗口类的风格
	wc.lpszClassName = szAppClassName;					   //窗口的类型名

	//2、注册窗口类（经过批准，同意）
	RegisterClass(&wc);

	//3、创建窗口（什么类型）
	HWND hWnd = CreateWindow(
		szAppClassName,										//窗口类型名
		L"F-3X俄罗斯方块",									//窗口的标题
		WS_BORDER | WS_CAPTION | WS_SYSMENU |WS_MINIMIZEBOX, //窗口的风格
		200, 100,											//窗口左上角坐标
		500, 630,											//窗口的宽和高
		NULL,												//父窗口句柄
		NULL,												//菜单句柄
		hInstance,											//应用程序实例句柄
		NULL												//附加信息
	);

	//4、显示窗口
	ShowWindow(hWnd, SW_SHOW);

	//5、更新窗口
	UpdateWindow(hWnd);

	//6、消息循环 
	MSG msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		//将虚拟键消息转化为字符消息
		TranslateMessage(&msg);
		//将消息分发给窗口处理函数
		DispatchMessage(&msg);
	}
	return 0;
}

//窗口处理函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;

	switch (uMsg)
	{
	case WM_CREATE:
		CreateTrtrisBlock();break;
	case WM_PAINT://窗口绘图消息
		//开始绘图
		hDC=BeginPaint(hWnd,&ps);

		OnPaint(hDC);

		//结束绘图
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE://窗口关闭消息
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY://窗口销毁信息
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//窗口绘图函数
void OnPaint(HDC hDC) 
{
	//画游戏边框
	Rectangle(hDC, 0, 0, 300, 600);

	//画方块
	DrawBlock(hDC);
}

//绘制方块
void DrawBlock(HDC hDC)
{
	for (int i = 0;i < 20;i++) //行
	{
		for (int j = 0;j < 10;j++) //列
		{
			if (g_arrBackground[i][j] == 1|| g_arrBackground[i][j]==2)
			{
				//创建画笔
				HPEN hPen = CreatePen(PS_SOLID, 1, RGB(50, 78, 188));
				HPEN oldPen = (HPEN)SelectObject(hDC, hPen);
				//创建画刷
				HBRUSH hBrush=CreateSolidBrush(RGB(51,201,255));
				HBRUSH oldBrush =(HBRUSH) SelectObject(hDC, hBrush);
				Rectangle(hDC, j * 30+1, i * 30+1, j * 30 + 30-1, i * 30 + 30-1);
				SelectObject(hDC, oldBrush);
			}
		}
	}
}

//随机生成俄罗斯方块
void CreateTrtrisBlock() 
{
	srand((UINT)time(NULL));
	int nIndex = rand() % 7;//0->6

	switch (nIndex) 
	{
	case 0:
		g_arrElsfk[0][0] = 1, g_arrElsfk[0][1] = 0, g_arrElsfk[0][2] = 0, g_arrElsfk[0][3] = 0;
		g_arrElsfk[1][0] = 1, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 1, g_arrElsfk[1][3] = 0;
		break;
	case 1:
		g_arrElsfk[0][0] =01, g_arrElsfk[0][1] = 0, g_arrElsfk[0][2] = 1, g_arrElsfk[0][3] = 0;
		g_arrElsfk[1][0] = 1, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 1, g_arrElsfk[1][3] = 0;
		break;
	case 2:
		g_arrElsfk[0][0] = 1, g_arrElsfk[0][1] = 1, g_arrElsfk[0][2] = 0, g_arrElsfk[0][3] = 0;
		g_arrElsfk[1][0] = 0, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 1, g_arrElsfk[1][3] = 0;
		break;
	case 3:
		g_arrElsfk[0][0] = 0, g_arrElsfk[0][1] = 1, g_arrElsfk[0][2] = 1, g_arrElsfk[0][3] = 0;
		g_arrElsfk[1][0] = 1, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 0, g_arrElsfk[1][3] = 0;
		break;
	case 4:
		g_arrElsfk[0][0] = 1, g_arrElsfk[0][1] = 1, g_arrElsfk[0][2] = 0, g_arrElsfk[0][3] = 0;
		g_arrElsfk[1][0] = 1, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 0, g_arrElsfk[1][3] = 0;
		break;
	case 5:
		g_arrElsfk[0][0] = 0, g_arrElsfk[0][1] = 1, g_arrElsfk[0][2] = 0, g_arrElsfk[0][3] = 0;
		g_arrElsfk[1][0] = 1, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 1, g_arrElsfk[1][3] = 0;
		break;
	case 6:
		g_arrElsfk[0][0] = 1, g_arrElsfk[0][1] = 1, g_arrElsfk[0][2] = 1, g_arrElsfk[0][3] = 1;
		g_arrElsfk[1][0] = 0, g_arrElsfk[1][1] = 0, g_arrElsfk[1][2] = 0, g_arrElsfk[1][3] = 0;
		break;
	}

	//复制到背景上
	for (int i = 0;i < 2;i++) 
	{
		for (int j = 0;j < 4;j++) 
		{
			g_arrBackground[i][j+4] = g_arrElsfk[i][j];
		}
	}
}
