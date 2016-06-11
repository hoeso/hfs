<?php
function dEcho( $file, $str )
{
  if( !isset($_REQUEST['d']) )
    return;
  echo"\n" . $file . " -- $str<br>\n";
}
if( isset($_REQUEST['d']) )
{
  $a_ = explode( "/", __file__ );
  $b_ = $a_[count($a_)-1];
  echo"\n" . $b_ . " -- POSTS:<br>";
  foreach( $_POST as $k=>$elem )
    echo"\nk : $k, elem: $elem<br>";
  echo"\n" . $b_ . " -- REQUESTS:<br>";
  foreach( $_REQUEST as $k=>$elem )
    echo"\nk : $k, elem: $elem<br>";
  if( 0/*isset($_FILES)*/ )
  {
    echo"\nFILES:<br>";
    foreach( $_FILES as $k=>$elem )
      echo"\nk : $k, elem: $elem<br>";
  }
}
function logModul( $str )
{
  echo"\n<!-- Modul $str: -->\n";
}
function logForkedModul( $str )
{
  echo"\n<!-- Modul $str: -->\n";
}
global $_E;
$_E['mn'] = $_REQUEST["mn"];
$_E['bodyClass'] = "main";
$_E['bodyId'] = "main";
$exitus="you don't exist. Go away!";
include("mn.prj");
include("tee.inc");
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN"
"http://www.w3.org/TR/html4/DTD/strict.dtd">
<html>
<head>
<title><?php
if( isset($_REQUEST['u']) )
  echo $_REQUEST['u'];
else
{?>
CFS<?php
}?>
</title>
<meta http-equiv="content-type" content="text/html;charset=utf-8">
<link rel="stylesheet" href="./fcs.css" media="screen" title="Flex Care Suite-Stylesheet" />
	<SCRIPT LANGUAGE="JavaScript" SRC="kalenderMattKruse.js"></SCRIPT>
	<SCRIPT LANGUAGE="JavaScript">
	var cal = new CalendarPopup();
	</SCRIPT>
</head>
<body class="<?php
echo $_E['bodyClass'];
?>" id="<?php
echo $_E['bodyId'];
?>" onLoad="cal.select(document.forms['example'].date1,'anchor1','MM/dd/yyyy');
//      cal.setMonthNames('Januar','Februar','März','April','Mai','Juni','Juli','August','September','Oktober','November','Dezember');
  //    cal.setDayHeaders('S','M','D','M','D','F','S');
      cal.setWeekStartDay(1);
    //  cal.setTodayText('Heute');
      return false;">
<FORM NAME="example">
(View Source of this page to see the example code)<br>
<INPUT TYPE="text" NAME="date1" VALUE="" SIZE=25>
<A HREF="#"
   NAME="anchor1" ID="anchor1"
   onChange="this.form.submit()"
>
</A>
<script>
var element = document.getElementById("header");
element.innerHTML = "New Header";
</script>
</FORM>
<?php
function logZustandswechsel( $str )
{
  echo"\n<!-- Eintreten in Zustand $str ... -->\n";
}

if( isset($_E['wZu']) )
  logZustandswechsel($_E['wZu']);
else if( isset($wZu) )
  logZustandswechsel($wZu);
else
  logZustandswechsel('kein Zustand gesetzt?!');
include("wZu.inc");
