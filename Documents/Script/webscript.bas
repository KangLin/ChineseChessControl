'����:����

'1����<script language="vbscript" src="..\..\..\..\..\�ҵ��ĵ�\Script\webscript.bas"></script>���,������ҳ�м�����ļ�
'2��������ʽ��<link rel="stylesheet" type="text/css" href="..\..\..\..\..\�ҵ��ĵ�\Script\��ʽ.css">

'����:�������Ϊ��ʾ,���Ϊ����ʾ,����ǲ���ʾ,���Ϊ��ʾ
'����:Ҫ���õĶ���
'�÷�:
'    1����<script>���,������ҳ�м�����ļ�
'    2�����ñ�ǩ<span>
'        <span class="ShowLink" onclick="Call Show(DispthMessageTable)">��ʾ����</span>��
'    3�����ñ������
'        <table class="TableStyle" id="DispthMessageTable" style="display:none">
Function Show(ShowObj)
If ShowObj.style.display = "" Then
   ShowObj.style.display = "none"
Else
   ShowObj.style.display = ""
End If
End Function

'����:��ʾ/������������
'�÷�:1����<script>���,������ҳ�м�����ļ�
'     2���Ƚ�����id="showall" & num
'        <span class="ShowLink" onclick="Call ShowAll()">��ʾ��������</span>
'     3���ٵ��ô˺���
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
          'document.all.showall1.innertext = "������������"
          document.all.item(i).innertext =  "������������"
       End If
   Next
End If
End Function
