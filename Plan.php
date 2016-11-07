<?php
require_once("KWmodel.php");
include("vektorQuart.prj"); // $quart
class Plan extends KWmodel
{
  protected $tag;

  function __construct($strDate, $filter="" )
  {
    parent::__construct($strDate, $filter);
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
    $str = "";
    if( 'k' == $what )
    {
    }
    else
    { // mit ID des MA filtern
      if( isset($_REQUEST['filterMA']) )
        $str = "&filterMA=" . $_REQUEST['filterMA'];
    }
    ?><table><tr><th><?php echo "[KW" . $this->Kalenderwoche . "] ";?></th><th>
    <?php
    if( isset($_REQUEST['k']) )
    {?>
      <img class="img20" src='images/rg1024-yellow-mail-18px.png' usemap="#mailMA">
      <map name="mailMA">
      <area shape=rect coords="0,0,18,18" title='Wochenplan senden an MA' href="./mn.php?mn=kw_tex&a=MAClientVS&c=<?php echo $what;?>&k=<?php echo $_REQUEST['k']; echo $str;?>&navi=KW&u=45 Klient#1">
      </map>
      <!-- img class="img19" src="images/grandma-penguin-18px.png" --><?php
    }?>
    </th><th>Morgens</th><th>Mittags</th><th>Nachmittags</th><th>Abends</th><th>Sonstiges</th></tr>
    <?php
    $i=0;
    $vgl = "";
    foreach ($this->tag as $dayofweek => $value)
    {
      ++$i;
      if( 1 == $i )
        continue;
      /*** Spalte 'Datum'            ***/
      lfSeitenquelltext();
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
//          ?><td></td><?php
        }
        /*** Spalte 'Morgens'            ***/
        ?><td><?php
        unset($m);
        $this->gibTerminMA( $m, $dimM, $this->Jahr, $this->Kalenderwoche, $i-1, $a[$k+1], 'morgens' ); // a k+1 : c.ID
        if( !$m[0] )
        { // nix gfundn worn :-(
        }
        else
        {
          for( $l=0; $l < count($m); $l += $dimM )
          {
            /*** Spalte 'Morgens'            ***/
            if( $l+1 > $dimM )
              echo "<br>";
            echo $m[$l] . "<br>" . $m[$l+1] . " - " . $m[$l+2];
          }
        }
        ?></td><?php
        /*** Spalte 'Mittags'            ***/
        ?><td><?php
        unset($m);
        $this->gibTerminMA( $m, $dimM, $this->Jahr, $this->Kalenderwoche, $i-1, $a[$k+1], 'mittags' ); // a k+1 : c.ID
        if( !$m[0] )
        { // nix gfundn worn :-(
        }
        else
        {
          for( $l=0; $l < count($m); $l += $dimM )
          {
            /*** Spalte 'Mittags'            ***/
            if( $l+1 > $dimM )
              echo "<br>";
            echo $m[$l] . "<br>" . $m[$l+1] . " - " . $m[$l+2];
          }
        }
        ?></td><?php
        /*** Spalte 'Nachmittags'            ***/
        ?><td><?php
        unset($m);
        $this->gibTerminMA( $m, $dimM, $this->Jahr, $this->Kalenderwoche, $i-1, $a[$k+1], 'nachmittags' ); // a k+1 : c.ID
        if( !$m[0] )
        { // nix gfundn worn :-(
        }
        else
        {
          for( $l=0; $l < count($m); $l += $dimM )
          {
            /*** Nachmittags'            ***/
            if( $l+1 > $dimM )
              echo "<br>";
            echo $m[$l] . "<br>" . $m[$l+1] . " - " . $m[$l+2];
          }
        }
        ?></td><?php
        /*** Spalte 'Abends'            ***/
        ?><td><?php
        unset($m);
        $this->gibTerminMA( $m, $dimM, $this->Jahr, $this->Kalenderwoche, $i-1, $a[$k+1], 'abends' ); // a k+1 : c.ID
        if( !$m[0] )
        { // nix gfundn worn :-(
        }
        else
        {
          for( $l=0; $l < count($m); $l += $dimM )
          {
            /*** 'Abends'            ***/
            if( $l+1 > $dimM )
              echo "<br>";
            echo $m[$l] . "<br>" . $m[$l+1] . " - " . $m[$l+2];
          }
        }
        ?></td>
        <td></td><?php // Sonstiges
        /*** das war die letzte Zelle    ***/
        ?></tr><?php
        if( $k < (count($a)-2) )
        { // vorletzter Klient dieses Tages
          lfSeitenquelltext();
	  ?><tr><td></td><?php
        }
      }
    }?>
    </tr>
    </table>
    <?php
  }
}
