<?
if( 1 )
{
  echo"\nPOSTS:<br>";
  foreach( $_POST as $k=>$elem )
    echo"\nk : $k, elem: $elem<br>";
  echo"\nREQUESTS:<br>";
  foreach( $_REQUEST as $k=>$elem )
    echo"\nk : $k, elem: $elem<br>";
}
$_E['mn'] = $_REQUEST["mn"];
$_E['bodyID'] = "main";
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
echo "{$_E['bodyID']}";
?>><?
function logZustandswechsel( $str )
{
  echo"\n<!-- Eintreten in Zustand $str ... -->\n";
}

logZustandswechsel($_E['wZu']);
include("wZu.inc");
?>
