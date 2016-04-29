<?php
require_once("KWmodel.php");
include("vektorQuart.prj"); // $quart
class KWview extends KWmodel
{
  protected $tag;

  function __construct($strDate)
  {
    parent::__construct($strDate);
    //var_dump($this->tag); echo "\n<br>";
  }
  function __get($var)
  {
    switch($var)
    {
      case 'Datum':
        return parent::__get('Datum');
      case 'DatumEU':
        return parent::__get('DatumEU');
      case 'Go':
        return parent::__get('Go');
      case 'Jahr':
        return parent::__get('Jahr');
      case 'Kalenderwoche':
        return parent::__get('Kalenderwoche');
      case 'KWweiter':
        return parent::__get('KWweiter');
      case 'KWzurueck':
        return parent::__get('KWzurueck');
      case 'Stop':
        return parent::__get('Stop');
      default:
        throw new Exception("KWview hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
  function show( $what, $how='initialen' )
  {
    global $quart;
    if( isset($_REQUEST["d"]) )
    {
      $a_ = explode( "/", __file__ );
      $b_ = $a_[count($a_)-1];
    }
    if( 'client' <> $what and 'mitarbeiter' <> $what )
    {
      dEcho( $b_, "KWview::show( [client|mitarbeiter] )" );
      return;
    }
    if( 'client' == $what )
    {
      $title = 'Mitarbeiter';
      $maORcl = "d"; // alles was nicht c ist, ist MA
      $NOTmaORcl = "c"; // alles was nicht c ist, ist MA
    }
    else
    {
      $title = 'Klient&#042;innen';
      $maORcl = "c";
      $NOTmaORcl = "d"; // alles was nicht c ist, ist MA
    }    if( 'client' == $what )
      $img = 'threepeople-24px.png';
    else
      $img = 'grandma-penguin-24px.png';
    ?><table><tr><?php
    if( 'initialen' == $how )
    {
      $text='n';
      if( 'client' == $what )
      {
        $concat = "CONCAT(LEFT(c.Name,1),LEFT(c.Vorname,1))";
      }
      else
      {
        $concat = "CONCAT(LEFT(m.Name,1),LEFT(m.Vorname,1))";
      }
    }
    else
    {
      $text='i';
      if( 'client' == $what )
      {
        $concat = "CONCAT(c.Name,' ',c.Vorname)";
      }
      else
      {
        $concat = "CONCAT(m.Name,' ',m.Vorname)";
      }
    }
    /*** 1. Header ausgeben           ***/
    $i=0;
    $ancor=0;
    foreach ($this->tag as $dayofweek => $value)
    { // Spalten-Ueberschriften anzeigen
      if( !$i )
      { // Pics der Umschalter Client o. MA
        ++$ancor;
        $kw = $this->Kalenderwoche;
        if( 'c' == $maORcl )
        {
	  $kw .= " Klient";
	  $NOTkw = " MA";
        }
	else
        {
	  $kw .= " MA";
	  $NOTkw = " Klient";
        }
        ?><td colspan=7>
	<img class="img18" src="images/<?php echo $img;?>" alt="zum Wochenplan" usemap="#maorcl<?php echo $ancor;?>">
	<a name='<?php echo $ancor;?>'></a>
        <map name="maorcl<?php echo $ancor;?>">
        <area shape=rect coords="0,0,18,18" title='<?php echo $title;?>' href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $maORcl;?>&k=<?php echo $this->Datum;?>&navi=KW&u=<?php echo $kw;?>#<?php echo $ancor;?>">
        </map>
	<img class="img18" src="images/guardar-18px.png" alt="KW speichern" usemap="#insertKW<?php echo $ancor;?>">
        <!--map name="insertKW<?php echo $ancor;?>">
        <area shape=rect coords="0,0,18,18" title='Plan f&uuml;r KW<?php echo $this->Kalenderwoche;?> speichern' href="./mn.php?mn=insertKW&a=MAClientVSKW&b=<?php echo $maORcl;?>&k=<?php echo $this->Datum;?>&navi=KW&u=<?php echo $kw;?>#<?php echo $ancor;?>">
        </map-->
        <a class="img18" href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $NOTmaORcl;?>&k=Y-m-d&navi=KW&u=<?php echo $this->DatumEU . " " . $NOTkw;?>#<?php echo $ancor;?>">Heute</a>
        <img class="img18" src="images/jean-victor-balin-arki-arrow-left-18px.png" alt="zur&uuml;ck" usemap="#zurueck<?php echo $ancor;?>">
        <map name="zurueck<?php echo $ancor;?>">
        <area shape=rect coords="0,0,18,18" title='KW <?php echo $this->Kalenderwoche - 1;?>' href="./mn.php?mn=kw&a=MAClientVSKW&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->KWzurueck;?>&navi=KW&u=<?php echo $kw - 1 . " " . $NOTkw;?>#<?php echo $ancor;?>">
        </map>
        <em class="img18">KW<?php echo $this->Kalenderwoche;?></em>
        <img class="img18" src="images/jean-victor-balin-arki-arrow-right-18px.png" alt="weiter" usemap="#weiter<?php echo $ancor;?>">
        <map name="weiter<?php echo $ancor;?>">
        <area shape=rect coords="0,0,18,18" title='KW <?php echo $this->Kalenderwoche + 1;?>' href="./mn.php?mn=kw&a=MAClientVSKW&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->KWweiter;?>&navi=KW&u=<?php echo $kw + 1 . " " . $NOTkw;?>#<?php echo $ancor;?>">
        </map><?php
        if( 'initialen' == $how )
          $img2 = "1430954247-18px.png";
        else
          $img2 = "matt-icons_emblem-minus-18px.png";?>
	<img class="img18" src="images/<?php echo $img2;?>" alt="Darstellung" usemap="#initialen<?php echo $ancor;?>">
	<a name='<?php echo $ancor;?>'></a>
        <map name="initialen<?php echo $ancor;?>">
        <area shape=rect coords="0,0,18,18" title='Darstellung' href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->Datum;?>&c=<?php echo $text;?>&navi=KW&u=<?php echo $this->Kalenderwoche . " " . $NOTkw;?>#<?php echo $ancor;?>">
        </map>
        </td></tr><tr><td></td><?php
        ++$i;
	continue;
      }?>
      <td><?php
      echo $dayofweek . " " . $value . "    ";
      ?></td><?php
      ++$i;
    }?>
    </tr><tr><?php
    /*** 2. Quart-Zeilen ausgeben     ***/
    $row = $this->Go;
    while( $row < $this->Stop )
    {
      $i=0;
      foreach ($this->tag as $dayofweek => $value)
      {
        if( !$i )
        { // Zeile mit Uhrzeit beginnen
          ?><td><?php echo "\n" . $quart[$row];?></td><?php
          ++$i;
	  continue;
        }?>
        <td><?php
        unset($a);
        $a[0]=0;// hier Feld 0 rein = Menge
        $a[1]=1;// hier Feld 1 rein = Initialen
        $a[2]=2;// hier Feld 2 rein = Name, Vorname
        $a[3]=3;// hier Feld 3 rein = [Client|MA].ID
	$dim=count($a);
        if( 'client' == $what )
        {
	  $sql = "SELECT cv.Menge, " . $concat . " AS sc, CONCAT(c.Name,',',c.Vorname), c.ID FROM MAClientVS mcv JOIN ClientVS cv ON (mcv. ClientVSID =cv.ID) JOIN Client c ON (cv. ClientID =c.ID) JOIN Jahr j ON (cv. JahrID =j.ID) JOIN KW k ON (cv. KWID =k.ID) JOIN Tag t ON (cv. TagID =t.ID) JOIN VS v ON (cv. VSID =v.ID) WHERE $this->Jahr=j.ID AND $this->Kalenderwoche=k.ID AND '$dayofweek'=t.SC AND $row=v.ID ORDER BY sc";
        }
	else
        {
	  $sql = "SELECT cv.Menge, CONCAT(LEFT(m.Name,1),LEFT(m.Vorname,1)) AS sc, CONCAT(m.Name,',',m.Vorname), m.ID FROM MAClientVS mcv JOIN ClientVS cv ON (mcv. ClientVSID =cv.ID) JOIN MAClient mc ON (mcv. MAClientID =mc.ID) JOIN MA m ON (mc.MAID=m.ID) JOIN Jahr j ON (cv. JahrID =j.ID) JOIN KW k ON (cv. KWID =k.ID) JOIN Tag t ON (cv. TagID =t.ID) JOIN VS v ON (cv. VSID =v.ID) WHERE mc.ClientID=cv.ClientID AND $this->Jahr=j.ID AND $this->Kalenderwoche=k.ID AND '$dayofweek'=t.SC AND $row=v.ID ORDER BY sc";
        }
        DB::gibFelderArray( $sql, $a );
        if( $a[0]==0 && $a[1]==1 && $a[2]==2 )
	{ // nix gfundn worn :-(
	  if( isset($_REQUEST['d']) )
	    $d="&d";
	  else
	    $d="";
          ?><a href="mn.php?mn=planend&a=ClientVS&sl=3&sl1=Client&sl2=<?php echo $row;?>&sl3=<?php echo $i;?>&navi=Plan&u=KW<?php echo $this->Kalenderwoche;?>&k=<?php echo $this->Kalenderwoche;?>&j=<?php echo $this->Jahr . $d;?>&planungVS_x" target="_blank" title="<?php echo $dayofweek . " " . $quart[$row];?>">&nbsp;</a><?php
	}
        else
	{ // Treffer, hier findet ein Client|MA Besuch statt:
	  for( $k=0; $k < count($a); $k += $dim )
	  {
	    $clutch = $dayofweek . $a[$k+1] . $quart[$row] . "|" . $a[$k+2]. "|" . $a[$k+3];
	    if ( !isset($aSC) or isset($aSC) and !isset($aSC[$clutch]) )
	    { // Zelle assoziativ belegen: "Wochentag . [MA|Client]-Initialen" = Menge
	      $aSC[$clutch] = $a[$k];
	    }
	  }
	}
	if( isset($aSC) )
          foreach ($aSC as $sc => &$counter)
	  {
            if( isset($_REQUEST["d"]) )
              dEcho( $b_, $sc );
	    if( substr($sc,0,2) == $dayofweek )
	    { // wir sind im richtigen Wochentag(=Spalte)
              $a__ = explode( "|", $sc );
              ?><a href="mn.php?mn=3653&a=Client&navi=CFS&ID=<?php echo $a__[2];?>&u=<?php echo substr($sc,2,2);?>&planungTag_x" target="_blank" title=<?php echo /*substr($sc,4,strlen($sc)-3)*/$a__[1] . ">"; // title: voller Name
              if( 'initialen' == $how )
	        echo substr($sc,2,2) . " "; // nur die Initialen
              else
	        echo substr($a__[1],0,12) . " "; // Name Vorname
              ?></a><?php
	      if( $counter )
	        --$counter;
	      if( !$counter )
	        unset($aSC[$sc]);
            }	
	  }
        ?></td><?php
        ++$i;
      }?>
      </tr><tr><?php
      if( !($row % 20) )
      {
        $j=0;
        foreach ($this->tag as $cltch => $datm)
        {
          if( !$j )
          {
            ++$ancor;
	    $kw = $this->Kalenderwoche;
            if( 'c' == $maORcl )
            {
	      $kw .= " Klient";
	      $NOTkw = " MA";
            }
	    else
            {
	      $kw .= " MA";
	      $NOTkw = " Klient";
            }
	    ?><td colspan=7><img class="img18" src="images/<?php echo $img;?>" alt="zum Wochenplan" usemap="#maorcl<?php echo $ancor;?>">
            <a name='<?php echo $ancor;?>'></a>
            <map name="maorcl<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" title='<?php echo $title;?>' href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $maORcl;?>&k=<?php echo $this->Datum;?>&navi=KW&u=<?php echo $kw;?>#<?php echo $ancor;?>">
            <img class="img18" src="images/guardar-18px.png" alt="KW speichern" usemap="#insertKW<?php echo $ancor;?>">
            <!--map name="insertKW<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" title='Plan f&uuml;r KW<?php echo $this->Kalenderwoche;?> speichern' href="./mn.php?mn=insertKW&a=MAClientVSKW&b=<?php echo $maORcl;?>&k=<?php echo $this->Datum;?>&navi=KW&u=<?php echo $kw . " " . $kw;?>#<?php echo $ancor;?>">
            </map-->
            <a class="img18" href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $NOTmaORcl;?>&k=Y-m-d&navi=KW&u=<?php echo $this->DatumEU . " " . $NOTkw;?>#<?php echo $ancor;?>">Heute</a>
            <img class="img18" src="images/jean-victor-balin-arki-arrow-left-18px.png" alt="zur&uuml;ck" usemap="#zurueck<?php echo $ancor;?>">
            <map name="zurueck<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" title='KW <?php echo $this->Kalenderwoche - 1;?>' href="./mn.php?mn=kw&a=MAClientVSKW&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->KWzurueck;?>&navi=KW&u=<?php echo $kw - 1 . " " . $NOTkw;?>#<?php echo $ancor;?>">
            </map>
            <em class="img18">KW<?php echo $this->Kalenderwoche;?></em>
            <img class="img18" src="images/jean-victor-balin-arki-arrow-right-18px.png" alt="weiter" usemap="#weiter<?php echo $ancor;?>">
            <map name="weiter<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" title='KW <?php echo $this->Kalenderwoche + 1;?>' href="./mn.php?mn=kw&a=MAClientVSKW&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->KWweiter;?>&navi=KW&u=<?php echo $kw + 1 . " " . $NOTkw;?>#<?php echo $ancor;?>">
            </map>
    	    <img class="img18" src="images/<?php echo $img2;?>" alt="Darstellung" usemap="#initialen<?php echo $ancor;?>">
    	    <a name='<?php echo $ancor;?>'></a>
            <map name="initialen<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" title='Darstellung' href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->Datum;?>&c=<?php echo $text;?>&navi=KW&u=<?php echo $this->Kalenderwoche . " " . $NOTkw;?>#<?php echo $ancor;?>">
            </map>
            </td></tr><tr><td></td><?php
            ++$j;
            continue;
          }?>
          <td><?php
          echo $cltch . " " . $datm . "    ";
          ?></td><?php
          ++$j;
        }?>
        </tr><tr><?php
      }
      ++$row;
    }?>
    </tr></table><?php
  }
}
