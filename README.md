##  至2026/3/30為止所作的更改

- 手柄的延遲判斷:在widget.cpp中，對 connect(zhukuang_widget,&zhukuang::clicked_start,this,[=]{} 進行修改
- 拍照速度更改:在 control_interface.cpp中，對read_socket_photograph() 縮短延遲判斷時間
- 拍照/錄影完後再點擊瀏覽頁面，會直接切到最後一頁

- 修改照片/影片的命名規則
- delete_all之後的行為BUG修改
  
  
