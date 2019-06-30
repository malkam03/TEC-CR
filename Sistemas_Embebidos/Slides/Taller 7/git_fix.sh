#!/bin/bash

grep -irlZ '=git' "$1" | xargs -0 sed -i 's/=git/=http/g'	
    
