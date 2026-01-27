def is_valid(row : int, col : int, num : int) -> bool:
    #Check row & col
    for i in range(9):
        if board[row][i] == num or board[i][col] == num: return False

    st_row = row // 3 * 3
    st_col = col // 3 * 3

    for i in range(st_row, st_row+3):
        for j in range(st_col, st_col+3):
            if board[i][j] == num: return False
    
    return True

def find_empty_cell() -> tuple[int, int]:
    for i in range(9):
        for j in range(9):
            if board[i][j] == 0: return i, j
    return None, None

def solve_sudoku() -> bool:
    row, col = find_empty_cell()

    if row is None: return True

    for num in range(1, 10):
        if is_valid(row, col, num):
            board[row][col] = num

            if solve_sudoku(): return True

            board[row][col] = 0
    return False

board = [
    [],
    [],
    [],
    [],
    [],
    [],
    [],
    [],
    [],
]

for i in range(9):
    a = input().split()
    for j in range(9):
        board[i].append(int(a[j]))

if solve_sudoku():
    print("Решение")
    for row in board:
        print(row)
else:
    print("Решений нет")
