## 至 2026/3/30 為止所作的更改

- 手柄的延遲判斷:在 widget.cpp 中，修改 `connect(zhukuang_widget,&zhukuang::clicked_start,this,[=]{}`
  
- 拍照速度更改:在 control_interface.cpp 中，對 `read_socket_photograph()` 縮短延遲判斷時間
- 拍照/錄影完後再點擊瀏覽頁面，會直接切到最後一頁
  1.在widget.cpp當中
- 修改照片/影片的命名規則
    <pre>cpp<br>connect(control_widget,&control_interface::socket_photograph_name,this,[=]{
        memset(result,0,sizeof(result));
        QString path;
        if(flag_USB==1)
        {
             path = "/mnt/USB_FLASH/Picture/";
        }
        else if(flag_USB==0 && flag_SD==1)
        {
             path = "/mnt/SD_CARD/Picture/";
        }
        int index = get_next_photo_index(path);
        QString fileName = QString("IMG_%1.jpg").arg(index, 6, 10, QChar('0'));  // 補零
        QString fullPath = path + fileName;
        strcpy(result, fullPath.toStdString().c_str());
        socketclient->write(result, strlen(result) + 1);
        photo_widget->photo_update();
        if(photo_max%6==0)
            photo_num = photo_totality+1;
        else
            photo_num = photo_totality;
    });<br> <pre>
- 
- delete_all 之後的行為 BUG 修改
  
  
