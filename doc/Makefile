.PHONY: html clean

html:
	doxygen 2>doxygen_warnings && \
		sed -r -e '/^.*instructions\/[a-z]+\.cpp:[0-9]+: warning: argument .* is not found in the argument list of .*$$/d' \
		       -e '/^.*instructions\/[a-z]+\.cpp:[0-9]+: warning: The following parameters of .* are not documented:$$/d' \
		       -e '/^  parameter .+$$/d' \
		       -i doxygen_warnings
	cat doxygen_warnings

tagfile: html
	doxytag -t tagfile html

clean:
	rm -rf html doxygen_warnings
