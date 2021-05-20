<?php
/************ ERICA MIT mn ***************************************************
 * 
 *****************************************************************************/

include "wrapperFK.inc";
include "wrapperListing.inc";

if( isset($_E['ident']) )
  $gruppenStaerke = $_E['ident'];

/************ ab hier FBS 2.0-Code *******************************************
 * 
 *****************************************************************************/
if( isset($_A['context']) )
  $_A['hitch'] = "f=" . gibFeld( $MySQLDb, $_A['context'], 0 );
if( isset($_E['nichtEinfuegen']) )
  $keinInsert = $_E['nichtEinfuegen'];
?>
