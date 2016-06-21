<!--Inhalte stammen von: http://www.web-toolbox.net/webtoolbox/formulare/checkbox-alle.htm#ixzz4CEDPaNPJ
www.clickstart.de-->

<script type="text/javascript">
function oiss(btn,frm){
btn.checked=!btn.checked;
cbs=frm['k[]'];
for(var i=0;i<cbs.length;i++)cbs[i].checked=btn.checked;
} 
function alle2(btn,frm){
btn.checked=!btn.checked;
cbs=frm['k[]'];
for(var i=1;i<cbs.length;i+=2)cbs[i].checked=btn.checked;
} 
function alle3(btn,frm){
btn.checked=!btn.checked;
cbs=frm['k[]'];
for(var i=2;i<cbs.length;i+=3)cbs[i].checked=btn.checked;
} 
function alle4(btn,frm){
btn.checked=!btn.checked;
cbs=frm['k[]'];
for(var i=3;i<cbs.length;i+=4)cbs[i].checked=btn.checked;
} 
</script>
