## 至 2026/3/30 為止所作的更改

- 手柄的延遲判斷:在 widget.cpp 中，修改 <pre>connect(zhukuang_widget,&zhukuang::clicked_start,this,[=]{
  }<pre>
  
- 拍照速度更改:在 control_interface.cpp 中，對 read_socket_photograph() 縮短延遲判斷時間
- 拍照/錄影完後再點擊瀏覽頁面，會直接切到最後一頁
  1.在widget.cpp當中
- 修改照片/影片的命名規則

- 
- delete_all 之後的行為 BUG 修改
  
  
