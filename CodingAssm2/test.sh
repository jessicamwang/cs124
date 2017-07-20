> resultreg
> resultstra100
> resultcomb
TIMEFORMAT=%7R
for i in `seq 100 100`;
    do
        >"randmat$i"
        for j in `seq 1 $((2*$(($i**2))))`
        do
            echo $[ 1 + $[ RANDOM % 100 ]] >> "randmat$i"
        done
        head -c -1 "randmat$i" > "randmat$i.tmp"
        mv "randmat$i.tmp" "randmat$i"
        for k in `seq 1 $i`
        do	
            if [ $(($k%1)) -eq 0 ]
            then
            	COMstra='./strassen $k $i randmat$i'

            	echo "testing strassen matrix mul: $i x $i n0: $k"
            	res1=$(date +%s.%N)
        		eval $COMstra > /dev/null
        		res2=$(date +%s.%N)
        		dtstra=$(echo "$res2 - $res1" | bc)
            	echo "$dtstra">> resultstra100
            fi

        done
    done