<?php // content="text/plain; charset=utf-8"



  $delai = 1; 
  $url = 'http://mondomaine.com/';
  header("Refresh: $delai;url=$url");
  
  
  // Actualise votre page actuelle après 5 secondes
    header("Refresh:1");
  
  
require_once ('jpgraph/src/jpgraph.php');
require_once ('jpgraph/src/jpgraph_line.php');

exec('mode COM6: BAUD=9600 PARITY=N data=8 stop=1 xon=on');
$fp =fopen("COM6", "w+");

$db = new PDO('sqlite:Us.sqlite');

$db->exec("CREATE TABLE dataUs(
	id INTEGER PRIMARY KEY,
	distance INTEGER,
	heure TIME)"
);

$arrayD = array();
$arrayT = array();

if(!$fp) {
       echo "Error";die();
}

for($i=0; $i<=10; $i++){
    sleep(1);   
    $resulta = fread($fp,10);
    $today = date("H:i:s");

    $dist = ord($resulta);
    $db->exec("INSERT INTO dataUs(distance, heure) VALUES ('$dist','$today')");

    array_push($arrayD,intval($dist));
    //$arrayT[] = int($today);

}

$datay1 = array(20,15,23,15);
$datay2 = array(12,9,42,8);
$datay3 = array(5,17,32,24);

// Setup the graph
$graph = new Graph(300,250);
$graph->SetScale("textlin");

$theme_class=new UniversalTheme;

$graph->SetTheme($theme_class);
$graph->img->SetAntiAliasing(false);
$graph->title->Set('Filled Y-grid');
$graph->SetBox(false);

$graph->SetMargin(40,20,36,63);

$graph->img->SetAntiAliasing();

$graph->yaxis->HideZeroLabel();
$graph->yaxis->HideLine(false);
$graph->yaxis->HideTicks(false,false);

$graph->xgrid->Show();
$graph->xgrid->SetLineStyle("solid");
$graph->xaxis->SetTickLabels(array('A','B','C','D'));
$graph->xgrid->SetColor('#E3E3E3');

// Create the first line
$p1 = new LinePlot($arrayD);
$graph->Add($p1);
$p1->SetColor("#6495ED");
$p1->SetLegend('Line 1');

$graph->legend->SetFrameWeight(1);

// Output line
$graph->Stroke();

?>