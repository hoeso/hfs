<?
/************ Input ********************
 * $ID         : Primaerschluessel des Datensatzes
 * $tableRE    : Name der Tabelle mit dem Primaerschluessel
 ***************************************/
$debug=0;
if( !isset($arrFK[$_E['entitaet']]) )
{
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
lesenRETabelle( $result, $MySQLDb, $_E['entitaet'], " WHERE ID=$ID" );
if( !$result )
{
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
spaltenNamenHolen( $result, $spaltenName );
$n = count($spaltenName);
if( $debug )
	echo"\nSpaltenzahl = $n<br>";
$hatAttribute = false;
$nFK=0;
for( $i=0; $i<$n; $i++)
  if( true == istForeignKeyName( $spaltenName[$i] ) )
  {
	 ++$nFK;
    if($debug)echo"\nFK-Name $spaltenName[$i]<br>";
  }
if( 1 == $nFK )
{// das war ja wohl nur der eigene Primaerschluessel 'ID'
  $_E['wZu']="anbietendKnopfZurueck";
  include("forkZu.inc");
}
?>
<hr>
<?
if($debug)echo"\nAnzahl FK's in Tabelle $tableRE = $nFK<br>";
$str=$_E['entitaet'];
$str=str_replace( "ae", "&auml;", $str );
echo "\n<H3>eine Beziehung von $str &auml;ndern ?</H3>";

$c=0;
for( $i=0; $i<$n; $i++)
	if( true == istForeignKeyName( $spaltenName[$i] ) )
		$FK['tabelle'][$c++] = str_replace( "ID", "", $spaltenName[$i] );
$arr = mysql_fetch_row( $result );
$anz = mysql_num_fields($result);
for( $i=1; $i < $anz; $i++ )
{
  if( isset($FK['tabelle'][$i]) and $FK['tabelle'][$i] )
  {
	 $FK['wert'][$i]=$arr[$i];
    if($debug){$str=$FK[tabelle][$i];echo"\nFK $str zeigt auf $arr[$i]<br>";}
  }
}
?>
<table border>
<?
for( $i=1; $i<$c; $i++)
{// FK-Tabellen nach ihrerseits bestehenden FK ueberpruefen
  $t=$FK['tabelle'][$i];
  $w=$FK['wert'][$i];

  $duDarfst=false;
  if( $arrFK[$_E['entitaet']] )
    foreach( $arrFK[$_E['entitaet']] as $key )
    {
      if( $key == $t )
      {/*** bestaetigen, dass dieser FK zum Aendern freigegeben ist ***/
        $duDarfst=true;
        break;
    }
  }
  if( false == $duDarfst )//FK ist nicht epxlizit erlaubt zum Aendern
    continue;

  echo"\n<tr>";

  if( isset( $_GET[Action] ) )
  {
    $str = urldecode($_GET[Action]);
    formularBeginnen( "./eiZu.php?wZu=$str&Titel=$t%20%E4ndern", "NAME='frm'");
  }
  else
    formularBeginnen( "./eiZu.php?wZu=aenderndFK&Titel=$t%20%E4ndern", "NAME='frm'");
  echo"<th>$t</th>";
  /*** Seinerseits jetzt die FK-Tabelle auslesen ***/
  lesenRETabelle( $result, $MySQLDb, $t, " WHERE ID=$w" );
  if( !$result )
  {
    $_E['wZu']="anbietendKnopfZurueck";
    include("forkZu.inc");
  }
  unset($spaltenName);
  spaltenNamenHolen( $result, $spaltenName );
  $n = count($spaltenName);
  $hatAttribute = false;
  $nFK=0;
  unset($FKFKSpalte);
  unset($FKFKWert);
  for( $j=0; $j<$n; $j++)
  {
	 if( true == istForeignKeyName( $spaltenName[$j] ) )
	 {
      ++$nFK;
		if( 2 == $nFK )
		{
		  $FKFKSpalte = $spaltenName[$j];
		  $arr = mysql_fetch_row( $result );
		  $FKFKWert=$arr[1];
		}
    }
  }
  if( 1 == $nFK )
  {//FK-Tabelle hat nur Attribute, also alle Datensaetze anbieten
	 lesenRETabelle( $result, $MySQLDb, $t, "" );
  }
  else if( isset($arrFKMM[$t]) and $arrFKMM[$t] )
  {
    $str0 = $arrFKMM[$t][0];
    $str1 = $arrFKMM[$t][1];
    $str0id = $str0 . 'ID';
    $str1id = $str1 . 'ID';
    $sql = "SELECT $t.ID, $str0.$str0 FROM $t, $str0, $str1 WHERE $str0id=$str0.ID AND $str1id=$str1.ID";
    $sql = "SELECT $t.ID, $str0.$str0, $str1.$str1 FROM $t, $str0, $str1 WHERE $str0id=$str0.ID AND $str1id=$str1.ID";
    if($debug){echo"\nMMFK = $t mit FKs $str0 $str1<br>$sql<br>";}
    $result = mysql_db_query( $MySQLDb, $sql );
  }
  else
  {// nochmal lesen und nur die Saetze mit gleichem FK anbieten
	 if( $debug )
		 echo "<td>nur Attribute auflisten mit WHERE $FKFKSpalte=$FKFKWert</td>";
    lesenRETabelle( $result, $MySQLDb, $t, " WHERE $FKFKSpalte=$FKFKWert" );
  }
  if( !$result )
  {
    $_E['wZu']="anbietendKnopfZurueck";
    include("forkZu.inc");
  }
  $anz = mysql_num_fields($result);
  unset($spaltenName);
  spaltenNamenHolen( $result, $spaltenName );
  $m = count($spaltenName);
  $d=0;
  unset($FK2);
  for( $j=0; $j<$m; $j++)
	 if( true == istForeignKeyName( $spaltenName[$j] ) )
		$FK2['tabelle'][$d++] = str_replace( "ID", "", $spaltenName[$j] );
  for( $j=1; $j < $anz; $j++ )
  {
	 if( isset($FK2['tabelle'][$j]) and $FK2['tabelle'][$j] )
		$FK2['wert'][$j]=$arr[$j];
  }
?>
<td bgcolor='#E8E8E8' align='center'><font size='-2'>
<SELECT NAME='SELECTFK' SIZE='1'>
<?
  while( $row=mysql_fetch_array( $result, MYSQL_NUM ) )
  {
    $id=true;
    $j=0;
    foreach( $row as $elem )
    {
      if( true==$id )
      {
        if( $debug )
	  echo"<td>FKid:$elem</td>";
        echo"\n\t<OPTION VALUE='$elem'";
        if( $elem == $w )
	  echo" SELECTED";
        echo">";
        $id=false;
      }
      else if( isset($FK2['tabelle'][$j]) and $FK2['tabelle'][$j] )
      {
        if( $debug )echo"<td>FKid:$elem</td>";
      }
      else
      {
        if( $debug )echo"<td>FKattr:$elem</td>";
          echo "$elem &gt;";
      }
      ++$j;
      //include("begrenzenFK.prj");// die naechsten 2 Zeilen funktionieren als include nicht: da wird nur 1 Listenelement angezeigt.
      if( 'Innendienst' == $_E['entitaet'] and 2 < $j )
        break;
    }
  }
?>
</SELECT>
</font></td>
<td>
<?
  echo"\n\t<INPUT TYPE='HIDDEN' NAME='Tabelle' VALUE='{$_E['entitaet']}'>";
  echo"\n\t<INPUT TYPE='HIDDEN' NAME='ID' VALUE='{$_E['ID']}'>";
  echo"\n\t<INPUT TYPE='HIDDEN' NAME='FKFeld' VALUE='$t";
  echo"ID'>";
  if( false == isset( $workflowAenderndFK ) )
    $workflowAenderndFK="";
  formularKnopf("Beziehung &uuml;bernehmen", $workflowAenderndFK);
?>
</td>
<?
  formularBeenden();
  echo"\n</tr>";
}
?>
</table>
