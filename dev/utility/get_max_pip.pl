#! /usr/bin/perl

@files = <$ARGV[0]/*>;
foreach $f (@files){
    get_pip($f);
}

foreach $snp (keys %pip){
    printf "%20s  %9.4e\n", $snp, $pip{$snp};
}


sub get_pip{
    my ($f) = @_;
    my $sum = 0;
    my $count = 0;
    my %rcd;

    open FILE, "$f";
    while(<FILE>){
        chomp;
        next if $_ !~ /\(\(/;
        my @data = split /\s+/, $_;
        shift @data until $data[0]=~/^\S/;

        if($data[2]>$pip{$data[1]}){
            $pip{$data[1]} = $data[2];
        }
    }

}
