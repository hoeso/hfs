<?
/************ ERICA MIT mn ***************************************************
 * 
 *****************************************************************************/
if( isset($_E['entitaet']) )
  $zielTabelle = $_E['entitaet'];

if( isset($_E["re"]) )
{
  $countRE = $_E["re"];
  for( $i=1; $i <= $_E['re'] and $i < 6; $i++ )
  {
    if( 1 == $i )
      $tableRE1 = $_E["re$i"];
    else if( 2 == $i )
      $tableRE2 = $_E["re$i"];
    else if( 3 == $i )
      $tableRE3 = $_E["re$i"];
    else if( 4 == $i )
      $tableRE4 = $_E["re$i"];
    else if( 5 == $i )
      $tableRE5 = $_E["re$i"];
  }
}
if( isset($_E["1n"]) )
{
  $countEM = $_E["1n"];
  for( $i=1; $i <= $_E['1n'] and $i < 6; $i++ )
  {
    if( 1 == $i )
      $tableEM1 = $_E["1n$i"];
    else if( 2 == $i )
      $tableEM2 = $_E["1n$i"];
    else if( 3 == $i )
      $tableEM3 = $_E["1n$i"];
    else if( 4 == $i )
      $tableEM4 = $_E["1n$i"];
    else if( 5 == $i )
      $tableEM5 = $_E["1n$i"];
  }
}
if( isset($_E["nn"]) )
{
  $countMM = $_E["nn"];
  for( $i=1; $i <= $_E['nn'] and $i < 6; $i++ )
  {
    if( 1 == $i )
      $tableMM1 = $_E["nn$i"];
    else if( 2 == $i )
      $tableMM2 = $_E["nn$i"];
    else if( 3 == $i )
      $tableMM3 = $_E["nn$i"];
    else if( 4 == $i )
      $tableMM4 = $_E["nn$i"];
    else if( 5 == $i )
      $tableMM5 = $_E["nn$i"];
  }
}
if( isset($_E["sl"]) )
{
  $countSL = $_E["sl"];
  for( $i=1; $i <= $_E['sl'] and $i < 6; $i++ )
  {
    if( 1 == $i )
    {
      $tableSL1 = $_E["sl$i"];
      $SL1 = $_E["stm$i"];
    }
    else if( 2 == $i )
    {
      $tableSL2 = $_E["sl$i"];
      $SL2 = $_E["stm$i"];
    }
    else if( 3 == $i )
    {
      $tableSL3 = $_E["sl$i"];
      $SL3 = $_E["stm$i"];
    }
    else if( 4 == $i )
    {
      $tableSL4 = $_E["sl$i"];
      $SL4 = $_E["stm$i"];
    }
    else if( 5 == $i )
    {
      $tableSL5 = $_E["sl$i"];
      $SL5 = $_E["stm$i"];
    }
  }
}
?>