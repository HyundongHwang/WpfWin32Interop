# WpfWin32Interop
닷넷과 win32간의 상호운용성 테스트 프로젝트

첫번째 예제로 WPF UI control library를 만들고 ( 계산기 UI를 만들었음. )
이를 win32 어플리케이션의 윈도우위에 차일드윈도우로 임베드하면서 띄우면서 win32와 wpf간의 통신을 하는 예제를 만들었음.

Win32, WPF, C++/CLI가 사용되었음.



### 스크린샷
![](https://raw.githubusercontent.com/HyundongHwang/WpfWin32Interop/master/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%BA%A1%EC%B3%90.png)



### WPF UI 컨트롤 코드
* xaml 코드
  * 간단한 계산기 UI
```xaml
<UserControl x:Class="HhdWpfLib.HhdCalcControl"
...>
    <StackPanel Orientation="Vertical">
        <TextBox x:Name="TbA" Margin="10, 10, 10, 0"></TextBox>
        <TextBox x:Name="TbB" Margin="10, 10, 10, 0"></TextBox>
        <Button x:Name="BtnResult" Margin="10, 10, 10, 0" Content="+"></Button>
        <TextBox x:Name="TbResult" Margin="10, 10, 10, 0" IsReadOnly="True"></TextBox>
    </StackPanel>
</UserControl>
```



* c# 비하인드 코드
  * 계산기로직
  * win32 -> wpf 호출할 함수 Init
  * wpf -> win32 호출할 델리게이트 정의
```c#
public delegate void HhdCallNativeDele(int thisObj, string msg);

public partial class HhdCalcControl : UserControl
{
    public HhdCallNativeDele CallNative;
    private int _thisObj;

    public HhdCalcControl()
    {
        InitializeComponent();
        this.BtnResult.Click += BtnResult_Click;
    }

    public void Init(int thisObj)
    {
        MessageBox.Show("HhdCalcControl.Init thisObj : " + thisObj);
        _thisObj = thisObj;
    }

    void BtnResult_Click(object sender, RoutedEventArgs e)
    {
        try
        {
            var a = int.Parse(this.TbA.Text);
            var b = int.Parse(this.TbB.Text);
            var c = a + b;
            this.TbResult.Text = c.ToString();
        }
        catch (Exception ex)
        {
            this.TbResult.Text = ex.ToString();
        }

        if (this.CallNative != null)
        {
            this.CallNative.Invoke(_thisObj, this.TbResult.Text);
        }
    }
}
```



### win32 어플리케이션
* 프로젝트 파일
  * 원래 UI로 설정가능하지만 너무 번거로와서 .vcproj파일을 덤프한다. 의미를 보고 UI로 제어하면 된다.
  * /clr 옵션을 주어 닷넷을 사용하도록 설정
  * 각종 닷넷 어셈블리 dll을 추가하도록 함.
```xml
<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" ToolsVersion="12.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <PropertyGroup Label="Globals">
    <ProjectGuid>{03F498E9-D9AF-4CA3-938E-C6D474C15A35}</ProjectGuid>
    <Keyword>Win32Proj</Keyword>
    <RootNamespace>Win32App</RootNamespace>
    <TargetFrameworkVersion>v4.5</TargetFrameworkVersion>
  </PropertyGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <ClCompile>
      <PrecompiledHeader>Use</PrecompiledHeader>
      <WarningLevel>Level3</WarningLevel>
      <Optimization>Disabled</Optimization>
      <PreprocessorDefinitions>WIN32;_DEBUG;_WINDOWS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <CompileAsManaged>true</CompileAsManaged>
      <DebugInformationFormat>ProgramDatabase</DebugInformationFormat>
      <MinimalRebuild>false</MinimalRebuild>
      <ExceptionHandling>Async</ExceptionHandling>
      <BasicRuntimeChecks>Default</BasicRuntimeChecks>
      <CallingConvention />
    </ClCompile>
  </ItemDefinitionGroup>
  <ItemGroup>
    <ProjectReference Include="..\HhdWpfLib\HhdWpfLib.csproj">
      <Project>{ee5ce6e4-f156-4d42-89c1-9d71174ca903}</Project>
      <Private>false</Private>
      <ReferenceOutputAssembly>true</ReferenceOutputAssembly>
      <CopyLocalSatelliteAssemblies>true</CopyLocalSatelliteAssemblies>
      <LinkLibraryDependencies>true</LinkLibraryDependencies>
      <UseLibraryDependencyInputs>false</UseLibraryDependencyInputs>
    </ProjectReference>
  </ItemGroup>
  <ItemGroup>
    <Reference Include="PresentationCore">
      <CopyLocalSatelliteAssemblies>true</CopyLocalSatelliteAssemblies>
      <ReferenceOutputAssembly>true</ReferenceOutputAssembly>
    </Reference>
    <Reference Include="PresentationFramework">
      <CopyLocalSatelliteAssemblies>true</CopyLocalSatelliteAssemblies>
      <ReferenceOutputAssembly>true</ReferenceOutputAssembly>
    </Reference>
    <Reference Include="System">
      <CopyLocalSatelliteAssemblies>true</CopyLocalSatelliteAssemblies>
      <ReferenceOutputAssembly>true</ReferenceOutputAssembly>
    </Reference>
    <Reference Include="WindowsBase">
      <CopyLocalSatelliteAssemblies>true</CopyLocalSatelliteAssemblies>
      <ReferenceOutputAssembly>true</ReferenceOutputAssembly>
    </Reference>
  </ItemGroup>
  </ImportGroup>
  ...
</Project>
```



* stdafx.h 파일
  * interop 헤더파일들 추가
  * 각 닷넷어셈블리들에 해당하는 네임스페이들을 추가
```cpp
#include <vcclr.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>



using namespace System;
using namespace System::Windows;
using namespace System::Windows::Documents;
using namespace System::Threading;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Windows::Media::Animation;
using namespace HhdWpfLib;
using namespace msclr::interop;
```

* win32 윈도우 구현파일
  * win32윈도우에 wpf control 임베딩
  * win32 에서 wpf 함수호출
  * win32 에서 wpf 델리게이트 등록
  * wpf 에서 델리게이트 호출해서 win32 함수 호출
```cpp
#include "stdafx.h"
#include "MainWnd.h"



using namespace System::Windows::Interop;



static void _OnFromManaged(int thisObj, String^ msg)
{
    MainWnd* pThis = (MainWnd*)(thisObj);
    std::wstring wMsg = marshal_as<std::wstring>(msg);
    pThis->OnFromManaged((wchar_t*)wMsg.c_str());
}

MainWnd::MainWnd()
{
}

MainWnd::~MainWnd()
{
}

void MainWnd::OnFromManaged(wchar_t* pwMsg)
{
    {
        CStringW strMsg = L"";
        strMsg.Format(L"MainWnd::OnFromManaged pwMsg : %s", pwMsg);
        ::MessageBoxW(NULL, strMsg, NULL, MB_OK);//hhddebug
    }
}

LRESULT MainWnd::_On_WM_CREATE(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    HwndSourceParameters params("MainWnd");
    params.PositionX = 0;
    params.PositionY = 0;
    params.Height = 300;
    params.Width = 300;
    params.ParentWindow = (IntPtr)this->m_hWnd;
    params.WindowStyle = WS_VISIBLE | WS_CHILD;
    HwndSource^ hwndSrcObj = gcnew HwndSource(params);

    this->m_HhdCalcControl = gcnew HhdCalcControl();
    this->m_HhdCalcControl->Init((int)this);
    this->m_HhdCalcControl->CallNative = gcnew HhdCallNativeDele(_OnFromManaged);
    hwndSrcObj->RootVisual = this->m_HhdCalcControl;
    HWND hwndHhdCalcControl = (HWND)hwndSrcObj->Handle.ToPointer();

    {
        CStringW strMsg = L"";
        strMsg.Format(L"MainWnd::_On_WM_CREATE hwndHhdCalcControl : %d\n", hwndHhdCalcControl);
        ::MessageBoxW(NULL, strMsg, NULL, MB_OK);//hhddebug
    }

    return 0;
}
```
