<?php
require_once("KWmodel.php");
include("vektorQuart.prj"); // $quart
class Plan extends KWmodel
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
      case 'Montag':
        return parent::__get('Montag');
      default:
        throw new Exception("Plan hat keine Eigenschaft $var.", 1 );
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
    if( 'k' <> $what and 'm' <> $what )
    {
      dEcho( $b_, "Plan::show( [client|mitarbeiter] )" );
      return;
    }
    if( 'k' == $what )
    {
    }
    else
    {
    }
    ?><table><tr><th>Datum</th><th>Name Kunde</th><th>Morgens</th><th>Mittags</th><th>Nachmittags</th><th>Abends</th><th>Sonstiges</th></tr>
    <?php
    $i=0;
    $vgl = "";
    foreach ($this->tag as $dayofweek => $value)
    {
      ++$i;
      if( 1 == $i )
        continue;
      /*** Spalte 'Datum'            ***/
      ?><tr><td><?php
      echo $dayofweek . " " . $value . "    ";
      ?></td><?php
      /*** Spalte 'Name Kunde'            ***/
      unset($k);
      $a = explode( " ", $value );
      $a_ = explode( ".", $a[0] );
      unset($a);
      $this->gibKlient( $a, $dim, $this->Jahr, $this->Kalenderwoche, $i-1 );
      if( !$a[0] )
      { // nix gfundn worn :-(
        ?><td><?php echo "--";
        ?></td></tr><?php
        continue;
      }
      for( $k=0; $k < count($a); $k += $dim )
      {
        if( "" == $vgl )
        {
          $vgl = $a[$k];
          $printName = true;
        }
        else if( $vgl <> $a[$k] )
        {
          $vgl = $a[$k];
          $printName = true;
        }
        else
          $printName = false;
        if( true == $printName )
        {
          ?><td><?php echo $a[$k];?></td><?php
          $printName = false;
        }
        else
        {
          ?><td></td><?php
        }
        ?></td><?php
        /*** Spalte 'Morgens'            ***/
        ?><td><?php
        echo $this->Kalenderwoche;
        ?></td><?php
        /*** Spalte 'Mittags'            ***/
        ?><td><?php
        ?></td><?php
        ?></tr><tr><td></td><?php
      }
    }?>
    </tr>
    </table>
    <?php
    return;?>
    <tr><?php
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
        $dim=0;
        unset($a);
        $this->gibTermine( $a, $dim, $what, $concat, $dayofweek, $row );
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
	    $clutch = $dayofweek . $a[$k+1] . $quart[$row] . "|" . $a[$k+2] . "|" . $a[$k+3] . "|" . $a[$k+4] . "|" . $a[$k+5] . "|" . $a[$k+6];
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
              if( 'client' == $what )
	      {
	        $ent=$a__[5];
                $str="&a=Client&planungTag_x";
	      }
              else
	      {
	        $ent=$a__[3];
                $str="&a=MA&planungMA_x";
	      }
              ?><a href="mn.php?mn=3653&navi=Plan&ID=<?php echo $a__[2];?>&u=<?php echo substr($sc,2,2) . $str;?>&MAClientVS=<?php echo $ent;?>#<?php echo $ent;?>" target="_blank" title=<?php echo $a__[1] . ">"; // title: voller Name
              if( 'initialen' == $how )
	        echo substr($sc,2,2) . " "; // nur die Initialen
              else
	        echo substr($a__[1],0,12) . "[" . $a__[4] . "] "; // Name Vorname
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
	    $NOTkw = $kw = $this->Kalenderwoche;
            if( 'c' == $maORcl )
            {
	      $kw .= " Klient";
	      $NOTkw .= " MA";
	      $kwTitel  = " MA";
            }
	    else
            {
	      $kw .= " MA";
	      $NOTkw .= " Klient";
	      $kwTitel  = " Klient";
            }
	    ?><td colspan=7>
	    <img class="img18" src="images/punaise-18px.png" alt="diese Uhrzeit" usemap="#pinnen<?php echo $ancor;?>">
	    <a name='<?php echo $ancor;?>'></a>
            <map name="pinnen<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" title='diese Uhrzeit pinnen' href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->Datum;?>&navi=KW&u=<?php echo $NOTkw;?>#<?php echo $ancor;?>">
            </map>
	    <img class="img18" src="images/<?php echo $img;?>" alt="zum Wochenplan" usemap="#maorcl<?php echo $ancor;?>">
            <a name='<?php echo $ancor;?>'></a>
            <map name="maorcl<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" title='<?php echo $title;?>' href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $maORcl;?>&k=<?php echo $this->Datum;?>&navi=KW&u=<?php echo $kw;?>#<?php echo $ancor;?>">
            <img class="img18" src="images/Copy-18px.png" alt="KW kopieren" usemap="#kopierenKW<?php echo $ancor;?>">
            <map name="kopierenKW<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" target="_blank" title='KW<?php echo $this->Kalenderwoche;?> kopieren' href="./mn.php?mn=kopierenKW&a=Kalenderwoche&sl=4&sl1=Jahr-%3E&sl2=KW-%3E&sl3=Jahr&sl4=KW&b=<?php echo $maORcl;?>&j=<?php echo $this->Jahr . $d;?>&k=<?php echo $this->Kalenderwoche;?>&navi=KW&u=<?php echo $this->Kalenderwoche;?>%20-&gt;KW%3F&kopierenKW_x#<?php echo $ancor;?>">
            </map>
            <a class="img18" href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $NOTmaORcl;?>&k=Y-m-d&navi=KW&u=<?php echo $this->DatumEU . " " . $NOTkw;?>#<?php echo $ancor;?>">Heute</a>
            <img class="img18" src="images/jean-victor-balin-arki-arrow-left-18px.png" alt="zur&uuml;ck" usemap="#zurueck<?php echo $ancor;?>">
            <map name="zurueck<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" title='KW <?php echo $this->Kalenderwoche - 1;?>' href="./mn.php?mn=kw&a=MAClientVSKW&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->KWzurueck;?>&navi=KW&u=<?php echo $kw - 1 . " " . $kwTitel;?>#<?php echo $ancor;?>">
            </map>
            <em class="img18">KW<?php echo $this->Kalenderwoche;?></em>
            <img class="img18" src="images/jean-victor-balin-arki-arrow-right-18px.png" alt="weiter" usemap="#weiter<?php echo $ancor;?>">
            <map name="weiter<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" title='KW <?php echo $this->Kalenderwoche + 1;?>' href="./mn.php?mn=kw&a=MAClientVSKW&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->KWweiter;?>&navi=KW&u=<?php echo $kw + 1 . " " . $kwTitel;?>#<?php echo $ancor;?>">
            </map>
    	    <img class="img18" src="images/<?php echo $img2;?>" alt="Darstellung" usemap="#initialen<?php echo $ancor;?>">
    	    <a name='<?php echo $ancor;?>'></a>
            <map name="initialen<?php echo $ancor;?>">
            <area shape=rect coords="0,0,18,18" title='Darstellung' href="./mn.php?mn=kw&a=MAClientVS&b=<?php echo $NOTmaORcl;?>&k=<?php echo $this->Datum;?>&c=<?php echo $text;?>&navi=KW&u=<?php echo $this->Kalenderwoche . " " . $kwTitel;?>#<?php echo $ancor;?>">
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
