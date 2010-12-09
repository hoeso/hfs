<?
$_E['mn'] = $_REQUEST["mn"];
$E_['bodyID'] = "main";
$exitus="you don't exist. Go away!";
include("mn.prj");
include("tee.inc");
?>
<html>
<head>
<title>ERICA Basics
</title>
<meta http-equiv="content-type" content="text/html;charset=utf-8">
</head>
<body id=<?
echo "{$E_['bodyID']}";
?>><?
function logZustandswechsel( $str )
{
  echo"\n<!-- Eintreten in Zustand $str ... -->\n";
}

logZustandswechsel($_E['wZu']);
include("wZu.inc");
?>
