<?php
unset( $candies );
$candies = "";
if( isset($_eCandy) )
{
  foreach( $_eCandy as $k => $elem )
    if( $elem )
      $candies .= "&$k=$elem";
}
echo "\n<form name='frm{$_E['entitaet']}' onSubmit='return pruefenEingaben(this)' action='./mn.php?mn={$_E['recipient']}&zielTabelle={$_E['entitaet']}$candies' method='post'";
if( isset($upload) )
{
  $upload=true;
  echo " enctype=\"multipart/form-data\"";
}
echo ">";
?>
