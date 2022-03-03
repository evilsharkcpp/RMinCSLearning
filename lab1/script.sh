#!/bin/bash
# Рекурсивная функция для обхода эл-тов каталога и сортировки
# по времени последнего изменения
function traverse()
{
    # Из-за рекурсивного поиска и того, что мы проверяем все каталоги,
    # игнорируем отсутствие каталога
    list=($(ls -1td $1/*/ 2> >(grep -v 'No such file or directory' >&2)))
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
    top="."
    if [ ! -z $1 ]; then
        top="$1"
        ls "$top"
        if [ $? -ne 0 ]; then
            return
        fi
    fi
    traverse "$top"
    echo "Total Directories: $count"
}
if [ "$#" -gt 1 ]; then
    echo "Illegal number of parameters"
else
    main "$1"
fi
