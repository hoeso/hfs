<?
$i = "0";
$str = $_E['projekt'] . 'Dir';

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
