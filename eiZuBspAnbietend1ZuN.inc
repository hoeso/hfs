<?php
/************ ERICA MIT mn ***************************************************
 * 
 *****************************************************************************/
if( isset($_E['entitaet']) && isset($_E['entitaetN']) )
{
  $countRE = 1;
  $tableRE1 = $_E['entitaetN'];
  $zielTabelle = $_E['entitaet'];
}
if( isset($_E['nSpaltenGruppieren']) )
  $gruppenStaerke = $_E['nSpaltenGruppieren'];
?>