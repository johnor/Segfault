CMOCK_SRC_DIR = $(CMOCK_DIR)/src
CMOCK_LIB_DIR = $(CMOCK_DIR)/lib
CMOCK_TARGET_DIR = $(CMOCK_DIR)/targets
CMOCK_CONFIG = $(CMOCK_TARGET_DIR)/apmaskin.yml
CMOCK_SRC = $(CMOCK_SRC_DIR)/cmock.c
CMOCK_OBJ = $(OBJ_DIR)/cmock.o

CFLAGS += -I$(CMOCK_SRC_DIR)
CFLAGS += -I$(MOCK_DIR)
GEN_MOCK = $(RUBY) $(CMOCK_LIB_DIR)/cmock.rb

$(CMOCK_OBJ) : $(CMOCK_SRC)
	@echo Compiling $^
	$(CC) $(CFLAGS) -c $^ -o $@
	@echo ' '

# gcc -MM -MG will not now the path of the files since they are not existing.
# However, other rules might, so adding targets with and without MOCK_DIR.
$(MOCK_DIR)/mock_%.c $(MOCK_DIR)/mock_%.h mock_%.h mock_%.c : %.h | $(MOCK_DIR)
	$(GEN_MOCK) -o$(CMOCK_CONFIG) $<
	@echo

$(MOCK_DIR)/%.o: $(MOCK_DIR)/%.c $(MOCK_DIR)/%.h
	@echo 'Compiling mock "$<" because of "$?"'
	$(CC) $(CFLAGS) -c $< -o $@
	@echo ' '
