<?php
$i = "0";
$str = $_E['projekt'] . 'Dir';

if( isset($_E['enableDbg']) && $_E['enableDbg'] )
  echo "<br>--dbg--- " . $str . ", docDir: " . $_SERVER[$str . $i] . " ---dbg--<br>";
$_E['rootDocuments'] = "";
while( isset($_SERVER[$str . $i]) )
{
  if (sha1($i) == $_REQUEST["a"] )
  {
    $_E['rootDocuments'] = $_SERVER[$str . $i];
    break;
  }
  ++$i;
}
if( !$_E['rootDocuments'] )
{
  echo "you don't exist. Go away!";
  exit;
}
// Output: 
// $_E['rootDocuments']
?>
