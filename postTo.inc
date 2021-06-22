<?php
unset( $candies );
$candies = "";
if( isset($_eCandy) )
{
  foreach( $_eCandy as $k => $elem )
    if( $elem )
      $candies .= "&$k=$elem";
}
if( isset($_REQUEST['d']) )
  $d="&d";
else
  $d="";
if( isset($_A['form_send']) )
  $fs = $_A['form_send'];
else
  $fs = "";
if( !isset($_E['recipient']) )
  $_E['recipient'] = "";

echo "\n<form name='frm{$_E['entitaet']}' onSubmit='return pruefenEingaben(this)' action='./mn.php?mn={$_E['recipient']}$d$fs&a={$_E['entitaet']}&b={$_E['entitaet']}-Instance%20is%20going%20to%20be%20saved%20...$candies";
if( isset($_E['klick1']) )
  echo "&klick1=" . $_E['klick1'];
if( isset($_E['navi']) )
  echo "&navi=" . $_E['navi'];
echo "' method='post'";
if( isset($upload) )
{
  $upload=true;
  echo " enctype=\"multipart/form-data\"";
}
echo ">";
?>
