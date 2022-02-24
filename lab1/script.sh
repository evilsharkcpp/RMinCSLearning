#!/bin/bash

#Рекурсивная функция для обхода эл-тов каталога и сортировки
#по времени последнего изменения
function traverse()
{
    
    list=($(ls -1td $1/*/))
    if [ ${#list[@]} -lt 1 ]; then
        return
    fi
    echo ""
    echo -n "Directory name: " 
    basename $1
    
    for folder in ${list[@]}
    do
        for i in ${list[@]}
        do
            tmp=$(basename $i)
            echo "|_$tmp"
        done
            traverse "$folder"  
            count=$(($count + 1))   
    done
    
}
function main()
{
    count=0
    traverse "$1"
    echo "Total Directories: $count"
}
if [ "$2" != "-a" ]; then
    main "$1" 2>/dev/null
else
    main "$1"
fi
