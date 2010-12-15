<?
unset( $candies );
if( isset($globalCandy) )
{
  foreach( $globalCandy as $k => $elem )
    if( $elem )
      $candies .= "&$k=$elem";
}
if( !isset($candies) )
  $candies = "";
echo "\n<form name='frm{$_E['entitaet']}' onSubmit='return pruefenEingaben(this)' action='./mn.php?mn={$_E['recipient']}$candies' method='post'";
if( isset($upload) )
{
  $upload=true;
  echo " enctype=\"multipart/form-data\"";
}
echo ">";
?>
