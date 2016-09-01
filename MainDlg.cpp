#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
 OPENFILENAME ofn;
 TCHAR szOpenFileNames[80*MAX_PATH];
 TCHAR szPath[MAX_PATH];
 TCHAR szFileName[80*MAX_PATH];
 TCHAR* p;
 int nLen = 0;

 ZeroMemory( &ofn, sizeof(ofn) );
 ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;
 ofn.lStructSize = sizeof(ofn);
 ofn.lpstrFile = szOpenFileNames;
 ofn.nMaxFile = sizeof(szOpenFileNames);
 ofn.lpstrFile[0] = '/0';
 ofn.lpstrFilter = TEXT("All Files(*.*)/0*.*/0");

 if( GetOpenFileName( &ofn ) )
 {  
  //把第一个文件名前的复制到szPath,即:
  //如果只选了一个文件,就复制到最后一个'/'
  //如果选了多个文件,就复制到第一个NULL字符
  lstrcpyn(szPath, szOpenFileNames, ofn.nFileOffset );
  //当只选了一个文件时,下面这个NULL字符是必需的.
  //这里不区别对待选了一个和多个文件的情况
  szPath[ ofn.nFileOffset ] = '/0';
  nLen = lstrlen(szPath);
  
  if( szPath[nLen-1] != '//' )   //如果选了多个文件,则必须加上'//'
  {
   lstrcat(szPath, TEXT("//"));
  }
  
  p = szOpenFileNames + ofn.nFileOffset; //把指针移到第一个文件
  
  ZeroMemory(szFileName, sizeof(szFileName));
  while( *p )
  {   
   lstrcat(szFileName, szPath);  //给文件名加上路径  
   lstrcat(szFileName, p);    //加上文件名  
   lstrcat(szFileName, TEXT("/n")); //换行   
   p += lstrlen(p) +1;     //移至下一个文件
  }
  MessageBox(NULL, szFileName, TEXT("MultiSelect"), MB_OK);
 }

        break;
		case IDC_NEW:
		{
			TCHAR wbcl[25600]={0};
			GetDlgItemText(hwnd,IDC_RICHEDIT,wbcl,sizeof(wbcl));
			if(strlen(wbcl)!=0)
			{   // MessageBox(hwnd,TEXT("nkj"),TEXT("WARNING"),MB_YESNO|MB_ICONWARNING);
			     int ret=MessageBox(hwnd,TEXT("是否保存当前文本"),TEXT("提醒"),MB_YESNO|MB_ICONQUESTION);
			     if(IDYES==ret)
				 {
				    goto loopsave;
				 }
				 else
				 {
					 SetDlgItemText(hwnd,IDC_RICHEDIT,"");
				 }
			}
		}
		break;
loopsave:case IDC_MENUSAVE :
		{
			TCHAR wbcl[25600]={0};
			GetDlgItemText(hwnd,IDC_RICHEDIT,wbcl,sizeof(wbcl));
			if(strlen(wbcl)==0)
			{   // MessageBox(hwnd,TEXT("nkj"),TEXT("WARNING"),MB_YESNO|MB_ICONWARNING);
			     MessageBox(hwnd,TEXT("请输入内容"),TEXT("提醒"),MB_OK|MB_ICONWARNING);
			}
			else
			{
				TCHAR wbl[25600]={0};
				GetDlgItemText(hwnd,IDC_RICHEDIT,wbl,sizeof(wbl));
				OPENFILENAME ofn;
					char szFile[256];
					ZeroMemory(&ofn,sizeof(ofn));
					ofn.lStructSize = sizeof(ofn);
					ofn.lpstrFile =  szFile;
					ofn.lpstrFile[0] = TEXT('\0');
					ofn.nMaxFile = sizeof(szFile);
					ofn.lpstrFilter = TEXT("ALL\0*.*\0Txt\0*.TXT\0");
					ofn.nFilterIndex = 2;
					ofn.nMaxFileTitle = 0;
					ofn.lpstrFileTitle = NULL;
					ofn.lpstrDefExt = TEXT ("txt") ; //默认扩展名
					ofn.hwndOwner = hwnd;
					ofn.lpstrInitialDir = NULL;
					ofn.Flags = OFN_EXPLORER |OFN_PATHMUSTEXIST |OFN_FILEMUSTEXIST;
				/*	if(GetOpenFileName(&ofn))
					{
						FILE *fp=fopen(szFile ,"r+"); //定义文件指针，读取指定目录文件
						TCHAR ch[25600];
						TCHAR ed[25600]={0};
						while(!feof(fp)) //检测指针是否到了文件尾
						{
							fgets(ch,sizeof(ch),fp);
							lstrcat(ed,ch);
							int w=strlen(ed);
							ed[w]=0;
						}
						SetDlgItemText(hwnd,IDC_RICHEDIT,ed);
						fclose(fp);
					}*/
				if(	GetSaveFileName(&ofn))
				{
					FILE *f=fopen(szFile,"w+");
					fputs(wbl,f);
					fclose(f);
					MessageBox(hwnd,TEXT("保存成功"),TEXT("WARNING"),MB_YESNO|MB_ICONWARNING);
				}
			}

		}
                break;
		case IDC_MENUHELP :
			{
                MessageBox(hwnd,TEXT("换行请按Ctrl+Enter\n"),TEXT("帮助"),MB_OK|MB_ICONWARNING);
			}
			break;
        default:
		break;
    }
}

void Main_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}

