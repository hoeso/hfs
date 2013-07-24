<?php
/** Aufrufendes Skript **** Variable *****************************************
 * formularFuerMM.inc : 
 *                    : tableA
 *                    : tableM
 *                    : tableB
 *                    : fUpdateB
 *                    : TabelleA
 *                    : TabelleM
 *                    : TabelleB
 *                    : SELECTA
 *                    : SELECTB
 * 
 *****************************************************************************/
/* zum Kopieren:
if( isset($_REQUEST[""]) )
  $ = $_REQUEST[""];
*/
if( isset($_REQUEST["tableA"]) )
  $tableA = $_REQUEST["tableA"];
if( isset($_REQUEST["tableM"]) )
  $tableM = $_REQUEST["tableM"];
if( isset($_REQUEST["tableB"]) )
  $tableB = $_REQUEST["tableB"];
if( isset($_REQUEST["fUpdateB"]) )
  $fUpdateB = $_REQUEST["fUpdateB"];
if( isset($_REQUEST["TabelleA"]) )
  $TabelleA = $_REQUEST["TabelleA"];
if( isset($_REQUEST["TabelleM"]) )
  $TabelleM = $_REQUEST["TabelleM"];
if( isset($_REQUEST["TabelleB"]) )
  $TabelleB = $_REQUEST["TabelleB"];
if( isset($_REQUEST["SELECTA"]) )
  $SELECTA = $_REQUEST["SELECTA"];
if( isset($_REQUEST["SELECTB"]) )
  $SELECTB = $_REQUEST["SELECTB"];
?>
