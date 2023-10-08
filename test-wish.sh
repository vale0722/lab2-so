#! /bin/bash

if ! [[ -x wish ]]; then
    echo "wish executable does not exist"
    exit 1
fi

echo "Wish executable exist"

./tester/run-tests.sh $*