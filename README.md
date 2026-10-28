# Danh bạ liên lạc — đếm tiền tố

Lời giải C++17 cho bài toán gồm tối đa 100.000 thao tác `add` / `find`,
mỗi xâu gồm chữ thường tiếng Anh và dài không quá 30 ký tự.

## Ý tưởng

Dùng cây Trie. Mỗi nút (khác gốc) biểu diễn một tiền tố và lưu `count`:
số liên lạc đã thêm có tiền tố đó.

- `add s`: đi theo các ký tự của `s`, tạo nút còn thiếu và tăng `count`
  tại mỗi nút đi qua.
- `find p`: đi theo các ký tự của `p`. Nếu thiếu một cạnh, in `0`;
  nếu đi hết, in `count` của nút cuối.

Mỗi lần `add` được tính là một liên lạc, kể cả khi xâu trùng với xâu đã thêm.
Một xâu cũng là tiền tố của chính nó.

## Chứng minh đúng

Ban đầu chưa có liên lạc nên mọi bộ đếm bằng 0.
Khi thêm xâu `s`, các nút trên đường đi của `s` biểu diễn chính xác các
tiền tố không rỗng của `s`. Tăng bộ đếm của các nút này thêm 1 và giữ nguyên
các nút khác sẽ duy trì bất biến: `count` tại mỗi nút bằng số liên lạc có
tiền tố tương ứng.

Vì vậy, nếu đường đi của `p` tồn tại, bộ đếm cuối đường chính là đáp án.
Nếu đường đi không tồn tại thì chưa có liên lạc nào có tiền tố `p`, nên đáp án
là 0. Cả hai trường hợp đều đúng.

## Độ phức tạp

Gọi `L` là độ dài xâu trong một thao tác, `S` là tổng độ dài các xâu đã thêm.
Các con của một nút được lưu bằng danh sách chỉ số để tiết kiệm bộ nhớ;
mỗi nút có tối đa 26 con.

- Mỗi thao tác: `O(26L) = O(L)` với bảng chữ cái cố định.
- Bộ nhớ: `O(S)`, tối đa `1 + 30n` nút. Trên môi trường GCC đã kiểm tra,
  mỗi nút chiếm 16 byte, tối đa khoảng 45,8 MiB cho vùng lưu nút.
- Không dùng đệ quy, không cần thư viện ngoài.

## Biên dịch và chạy

```sh
g++ -std=c++17 -O2 -Wall -Wextra -Wpedantic main.cpp -o /tmp/dsa-contacts
/tmp/dsa-contacts < input.txt
```

Với ví dụ trong đề, chương trình in:

```text
2
0
3
```
