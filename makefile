.DEFAULT_GOAL := help

help:
	@echo "To run a command use: make <command>"
	@echo "                                    "
	@echo "          General Commands           "
	@echo "          ----------------           "
	@echo "generate-docs:        Genrate the documentation of the project using the Doxyfile."
	@echo ""   
	@echo "help:                 Display this message."

generate-docs:
	doxygen ./Doxyfile