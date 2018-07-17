use Cwd 'abs_path';

$tissue = "TISSUE";
$dir = $ARGV[0];
@files = <$dir/*>;
$count=0;
if(defined($ARGV[1])){
    $tissue = $ARGV[1];
}
#

#$count = 0;
foreach $f (@files){
#   $count++;
    process_fm($f);
#   last if $count == 100;
}



sub process_fm{
	my ($f) = @_;
	
        ################################################################
        #                                                              #
        #   MODIFY HERE IF GENE NAME INSTEAD OF FILE NAME IS DESIRED   #    
        #                                                              #     
        ################################################################

        
        my $gene = $f;
        $gene =~ s/\/\//\//g;

	open FILE, "grep \\\{ $f | ";
	my %cpip;
	while(<FILE>){
		s/\{//;
		s/\}//;
		my @data = split /\s+/, $_;
		shift @data until $data[0]=~/^\S/;
                next if $data[2]<0.25;
		$cpip{$data[0]} =$data[2];
	}	

	my %cluster;
	open FILE, "grep \\\(\\\( $f | ";
	while(<FILE>){
		my @data = split /\s+/, $_;
		shift @data until $data[0]=~/^\S/;
		next if $data[-1] == -1;
		my $cid = $data[-1];
	        $cluster{$cid}->{$data[1]} = $data[2];
        }	
        
	my $con = "";
        foreach $cc (sort {$a<=>$b} keys %cpip ){ 
		foreach $snp (sort { $cluster{$cc}->{$b} <=> $cluster{$cc}->{$a} } keys %{$cluster{$cc}}){
			$con .=  sprintf "%25s\t%25s\t%2d\t%7.3f\t%20s\t%7.3e\n",$tissue,$gene,$cc,$cpip{$cc},$snp,$cluster{$cc}->{$snp};
		}
	}
	if($con !~ /chrX/ || $con !~ /chrY/){
		print  "$con";	
	}

}


