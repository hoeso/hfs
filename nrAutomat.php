<html>
<head>
<title>
DBG
</title>
</head>
<body>
<?php
if( isset($_REQUEST["a"]) )
{
  ?><a href="./nrAutomat.php"> weniger ... </a><?php
}
else
{
  ?><a href="./nrAutomat.php?a=1"> mehr ... </a><?php
}
?>
<pre>
<?php
$ex="";
if( isset($_REQUEST["a"]) )
  $ex = " -e exitus";
$str = shell_exec( "/bin/grep -e case" . $ex . " -e wZu mn.prj" );
echo $str;
?>
</pre>
<?php
if( isset($_REQUEST["a"]) )
{
  ?><a href="./nrAutomat.php"> weniger ... </a><?php
}
else
{
  ?><a href="./nrAutomat.php?a=1"> mehr ... </a><?php
}
?>
</body>
</html>
