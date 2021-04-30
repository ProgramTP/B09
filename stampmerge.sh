delimiter="$1"
append(){
	src="$1"
	tgt="$2"
	srclines=`wc -l "$src" | cut -c1`
	i=1
	#echo "To Append: $toappend"
	date=$(echo "$src" | cut -c 1-10)
	yes "$date" | head -n "$srclines" > tempdates.txt
	if [ "$delimiter" = "" ] || [ "$delimiter" = " " ]; then
		paste -d " " tempdates.txt ${src} >> ${tgt}
	else
		paste -d "$delimiter" tempdates.txt ${src} >> ${tgt}
	fi
	rm -r tempdates.txt
}
check(){
    for file in *; do
    	arg=$(echo "$file" | grep '^[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9].log$')
		if [ "$?" -eq 0 ]; then
			monthly=$(echo "$arg" | cut -c 1-7)
			append "$arg" "$monthly.log"
		fi   
    done
}
check
