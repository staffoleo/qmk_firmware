docker run \
       --rm \
       -e keyboard=tada68 \
       -e keymap=default \
       -e subproject="" \
       -v C:\GitRepositories\qmk_firmware:/qmk:rw \
       -w /qmk \
       edasque/qmk_firmware \
       make tada68-default-bin