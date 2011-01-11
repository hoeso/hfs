<?
if( 0 )
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
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN"
"http://www.w3.org/TR/html4/DTD/strict.dtd">
<html>
<head>
<title>ERICA Basics
</title>
<meta http-equiv="content-type" content="text/html;charset=utf-8">
</head>
<link rel="stylesheet" href="./erica.css" media="screen" title="erica Stylesheet" />
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
