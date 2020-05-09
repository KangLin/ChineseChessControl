'作者:康林

'1、用<script language="vbscript" src="..\..\..\..\..\我的文档\Scrpit\webscrpit.bas"></script>标记,先在网页中加入此文件
'2、加入样式：<link rel="stylesheet" type="text/css" href="..\..\..\..\..\我的文档\Scrpit\样式.css">

'功能:如果对象为显示,则变为不显示,如果是不显示,则变为显示
'参数:要设置的对象
'用法:
'    1、用<script>标记,先在网页中加入此文件
'    2、设置标签<span>
'        <span class="ShowLink" onclick="Call Show(DispthMessageTable)">显示文字</span>　
'    3、设置表格类型
'        <table class="TableStyle" id="DispthMessageTable" style="display:none">
Function Show(ShowObj)
If ShowObj.style.display = "" Then
   ShowObj.style.display = "none"
Else
   ShowObj.style.display = ""
End If
End Function

'功能:显示/隐藏所有文字
'用法:1、用<script>标记,先在网页中加入此文件
'     2、先将对象id="showall" & num
'        <span class="ShowLink" onclick="Call ShowAll()">显示所有文字</span>
'     3、再调用此函数
allon = 0
Function ShowAll()
If allon = 1 Then
   document.location.href = document.location.href
Else
   For i = 0 To document.all.length - 1
       document.all.item(i).style.display = ""
   Next
   allon = 1
   For i = 0 To document.all.length - 1
       If LCase(Left(document.all.item(i).id, 7)) = "showall" Then
          'document.all.showall1.innertext = "隐藏所有文字"
          document.all.item(i).innertext =  "隐藏所有文字"
       End If
   Next
End If
End Function