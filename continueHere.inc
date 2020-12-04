<?php
if( isset($_REQUEST["d"]) )
{
  $a_ = explode( "/", __file__ );
  $b_ = $a_[count($a_)-1];
}
if( isset($_REQUEST["d"]) && isset($_REQUEST["navi"]) )
  dEcho( $b_, "navi: " . $_REQUEST["navi"] );

include "continueHere.prj";
  
if( isset($_REQUEST['d']) )
  foreach( $candyURL as $k => $elem )
    $candyURL[$k] .= "&d";
if( isset($_REQUEST["navi"]) )
  foreach( $candyURL as $k => $elem )
    $candyURL[$k] .= "&navi=" . $_REQUEST["navi"];
// sind die Candidates bereits Teil der URL?
/*** hier geht es darum, dass wenn ein Candidate bereits ***
 *** mit ein name-value Paar mit dem Primaerschluessel   ***
 *** seiner Instanz bildet, es nicht ein 2. Mal gebildet ***
 *** wird
 ***/
foreach( $_eCandy as $k => $elem )
  if( isset($_REQUEST["$k"]) )
    $_eCandy[$k] = $_REQUEST["$k"];

// updatingPE ...
if( isset($tableREfake) and isset($ID) )
{
  if( isset( $_eCandy[$tableREfake] ) )
    $_eCandy[$tableREfake] = $ID;
}
else if( isset($tableRE) and isset($ID) )
{
  if( isset( $_eCandy[$tableRE] ) )
     $_eCandy[$tableRE] = $ID;
}
else if( isset($_E['entitaet']) and isset($_E['ID']) )
  $_eCandy[$_E['entitaet']] = $_E['ID'];

$a_ = explode( "/", __file__ );
$b_ = $a_[count($a_)-1];
foreach( $_eOverlay as $k => $elem )
{
  if( isset($_REQUEST["d"]) )
    dEcho( $b_, $k . "=" . $elem );
  if( isset($_E['entitaet']) && isset($_eOverlay[$_E['entitaet']]) && $_E['entitaet'] == $k )
  {
    $_eCandy[$elem]=$_eCandy[$k];
    $_eCandy[$k]=0;
  }
}
?>
