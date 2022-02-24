#!/bin/bash

#Рекурсивная функция для обхода эл-тов каталога и сортировки
#по времени последнего изменения
function traverse()
{
    count=$(($count + 1))
    list=($(ls -1td $1/*/))
    if [ ${#list[@]} -eq 0 ]; then
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
    done
    
}
function main()
{
    count=0
    traverse "$1"
    echo "Total Directories: $count"
}
main "$1"  
