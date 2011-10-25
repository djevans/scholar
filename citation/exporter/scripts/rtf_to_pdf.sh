#!/bin/bash
clear
/opt/libreoffice3.4/program/soffice --headless --nologo --invisible --nofirststartwizard -convert-to pdf:$1 -outdir $2