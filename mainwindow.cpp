#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    Viewer_def_size{800,600},
    logo(":images/logo.png"),
    logo_error(":images/logo_error.png")
{
    std::cout<<"setupUI!\n";
    ui->setupUi(this);


    Viewer.setVisible(false);
    Viewer.setActive(false);
    Viewer.setKeyRepeatEnabled(false);
    std::cout<<"window created!\n";
    ui->progress_label->setText("Hello\n");
    ui->progressBar->hide();




}

MainWindow::~MainWindow()
{
    std::cout<<"Destructor called\n";
    Viewer.close();
    std::cout<<"Viewer.close called\n";
    delete ui;
}





void MainWindow::on_load_pushButton_clicked()
{


    QStringList file_list=QFileDialog::getOpenFileNames(this,"Wybor plikow","","All (*.*);;BMP (*.bmp *dib);;AAJW(*.aajw)");

    QString text=QString("%1  %2").arg(file_list.size(),sf::Texture::getMaximumSize());
    unsigned int siz=sf::Texture::getMaximumSize();
    text.append(QString::number(siz));

    for ( QStringList::const_iterator it = file_list.begin(); it != file_list.end(); ++it )
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        QFileInfo f=(*it);
        newItem->setText(f.fileName());
        QVariant data(*it);
        newItem->setData(Qt::WhatsThisRole,data);
        ui->listWidget->addItem(newItem);
        ui->progress_label->setText(QString("Loaded ")+f.fileName());

    }
}

bool MainWindow::quit_ask()
{
    QMessageBox::StandardButton reply; reply = QMessageBox::question(this, "Quit", "Do you want to quit?",
    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        qDebug() << "Yes was clicked";
        return true;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (quit_ask()) {
        Viewer.close();

        event->accept();
    } else {
        event->ignore();
    }
}




void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{

    if(!Viewer.isOpen())
    {
        std::cout<<"Recreating window!\n";
        Viewer.create(sf::VideoMode(Viewer_def_size.x,Viewer_def_size.y),"Viewer");
        Viewer.setVisible(false);
        Viewer.setActive(false);

    }
    else
    {
        qDebug()<<"Viewer already open!\n";
        return;
    }

    SFML_Objects Trio;

    qDebug() <<"Double click before display\n";
    MainWindow::SFML_display(item,Trio,Viewer);
    qDebug() <<"SFML Clear wywolany\n";



}


bool MainWindow::SFML_load(QListWidgetItem* item,SFML_Objects &obj,sf::RenderWindow &Window)
{

    std::string name= item->data(Qt::WhatsThisRole).toString().toStdString();
    Scale scale(Window.getSize().x,Window.getSize().y);

    if(!obj.Texture->loadFromFile(name))
    {
        SFML_QRes(obj,logo_error);


        scale.adjust(obj.Texture->getSize().x,obj.Texture->getSize().y);
        obj.Sprite->setScale(scale.getXScale(),scale.getYScale());
        obj.Sprite->setPosition(scale.getPosX(),scale.getPosY());

        return false;
    };


    obj.Sprite->setTexture(*obj.Texture,true);

    scale.adjust(obj.Texture->getSize().x,obj.Texture->getSize().y);
    obj.Sprite->setScale(scale.getXScale(),scale.getYScale());
    obj.Sprite->setPosition(scale.getPosX(),scale.getPosY());


    return true;
}

bool MainWindow::SFML_QRes(SFML_Objects &obj,QResource &res)
{

    if(!obj.Texture->loadFromMemory((const void*)res.data(),(std::size_t)res.size(),sf::IntRect()))
        return false;

    obj.Sprite->setTexture(*obj.Texture,true);

    return true;
}

void MainWindow::SFML_display(QListWidgetItem* item,SFML_Objects &obj,sf::RenderWindow &Window)
{
    std::cout<<"Double clicked!\n";

    QListWidget *QList=item->listWidget();
    QList->setCurrentItem(item);

    qDebug() <<"items in list"<<QList->count();
    qDebug() <<"current item row "<<QList->currentRow();
    int index=QList->currentRow();
    Window.clear();
    Window.setVisible(true);

    Scale scale(Window.getSize().x,Window.getSize().y);

    SFML_load(item,obj,Window);
    std::cout<<"Before loop!\n";
    Window.draw(*obj.Sprite);
    Window.display();

    sf::Event event;
    while (Window.isOpen())
    {

        while (Window.pollEvent(event))
        {

            if(event.type==sf::Event::Closed)
            {
                qDebug() <<"\tEvent closed activated\n";


                SFML_QRes(obj,logo);
                Window.clear();
                Window.close();

            }

            if (event.type==sf::Event::Resized)
            {
                Window.clear();

                std::cout << "Resized: [" << event.size.width << "; " << event.size.height << "]" << std::endl;
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                Window.setView(sf::View(visibleArea));

                scale.setframeX(event.size.width);
                scale.setframeY(event.size.height);
                scale.adjust(obj.Texture->getSize().x,obj.Texture->getSize().y);
                obj.Sprite->setScale(scale.getXScale(),scale.getYScale());
                obj.Sprite->setPosition(scale.getPosX(),scale.getPosY());



                Window.draw(*obj.Sprite);
                Window.display();
            }

            if(event.type==sf::Event::KeyPressed)
            {
                qDebug()<<"pre index"<<index;
                qDebug()<<"key pressed\n";
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    if(++index>=QList->count())
                    {
                        index=0;
                    }
                    qDebug() <<"index="<<index;


                    QList->setCurrentRow(index);
                    item=QList->currentItem();

                    if(!SFML_load(item,obj,Window))
                    {
                        ui->progress_label->setText("Failed to load the image to texture!\n");
                        ui->progress_label->repaint();

                    }

                    Window.clear();
                    Window.draw(*obj.Sprite);
                    Window.display();

                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    if(--index<0)
                    {
                        index=QList->count()-1;
                    }
                    qDebug() <<"index="<<index;
                    QList->setCurrentRow(index);
                    item=QList->currentItem();


                    if(!SFML_load(item,obj,Window))
                    {
                        ui->progress_label->setText("Failed to load the image to texture!\n");
                        ui->progress_label->repaint();

                    }

                    Window.clear();
                    Window.draw(*obj.Sprite);
                    Window.display();
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {

                    SFML_QRes(obj,logo);
                    Window.clear();
                    Window.close();
                }
                //scale.setX(obj.Texture->getSize().x);
                //scale.setY(obj.Texture->getSize().y);

            }

             // process event...

        }


    };

    return;


}


void MainWindow::on_remove_selected_pushButton_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(item));

        qDebug("Removed item\n");
    }
    items.clear();

    return;
}






void MainWindow::on_convert_pushButton_clicked()
{
    uint8_t compression=0;

    //RUN conversion
    if(ui->radioButton->isChecked())
        compression=1;
    else if(ui->radioButton_2->isChecked())
        ;//set param
    else if(ui->radioButton_3->isChecked())
        ;//set apram

    Viewer.close();

    std::time_t start = std::time(NULL);
    unsigned index = ui->listWidget->count();
    ui->progressBar->setValue(0);
    ui->progressBar->show();
    for(int i=index-1;i>=0;--i)
    {

        QListWidgetItem* item=ui->listWidget->takeItem(i);



            std::string file=item->data(Qt::WhatsThisRole).toString().toStdString();
            QString filename=item->text();
            std::vector<uint8_t> vector;
            ImgBaseInfo info;

            if(filename.endsWith(".bmp",Qt::CaseInsensitive) || filename.endsWith(".dib",Qt::CaseInsensitive))
            {
                vector=Vec_Extr::img_extract(file,info,Vec_Extr::RGB);
                qDebug()<<"ile el="<<vector.size();
                qDebug()<<"size of typu "<<sizeof(uint8_t);
                qDebug()<<"total="<<(vector.size()*sizeof(uint8_t))/1024;
                qDebug()<<"rozmiar x="<<info.size.x<<" y="<<info.size.y;
                if(!vector.empty())
                    {

                    convert(vector,file,info,compression);
                    //INSERT CONVERTING METHOD that grabs vector, and filename (to be extracted from item) (if not .dib, .bmp or vec=empty then skip method and log an error)
                    }
            }


            qDebug("Removed item\n");
            ui->progress_label->setText("processed "+ item->text());
            ui->progress_label->repaint();
            ui->progressBar->setValue(100/float(i));

            delete item;



    }

    ui->progress_label->setText("total time: " + QString::number(std::difftime(std::time(NULL), start))+" sec");
    ui->progressBar->hide();
    ui->listWidget->clear();
    return;


}

void MainWindow::on_reconvert_pushButton_clicked()
{
    Viewer.close();

    std::time_t start = std::time(NULL);
    unsigned index = ui->listWidget->count();
    ui->progressBar->setValue(0);
    ui->progressBar->show();
    for(int i=index-1;i>=0;--i)
    {

        QListWidgetItem* item=ui->listWidget->takeItem(i);
        QString filename=item->text();
        std::string file=item->data(Qt::WhatsThisRole).toString().toStdString();

        qDebug() << "filename"<<filename;
        qDebug() << "file="<<item->data(Qt::WhatsThisRole).toString();
        if(filename.endsWith(".aajw",Qt::CaseInsensitive))
        {
            reconvert(file);
        }
        ui->progressBar->setValue(100/float(i));
        delete item;

    }
    ui->progress_label->setText("total time: " + QString::number(std::difftime(std::time(NULL), start))+" sec");
    ui->progressBar->hide();
    ui->listWidget->clear();
    return;
}

/*! Metoda zajmujaca sie konwersja bitmapy na nowy format */
void MainWindow::convert(std::vector<uint8_t> vector,std::string name,ImgBaseInfo info,const uint8_t compression)
{

    std::ofstream ofs(name+".aajw", std::ios::binary);
    qDebug()<<"PRZED SBC, vector.size="<<vector.size();
    SevenBitComp SBC;
    std::vector<uint8_t> vec_compressed;

    std::ofstream ofs2(name+".txt",std::ios::trunc);
    for(uint32_t i=0;i<vector.size();i++)
        ofs2<<(int)vector[i]<<"\n";



    SBC.compress(vector,vec_compressed);
    //vec_compressed=vector;

    vector.clear();
    vector.resize(1);
    qDebug()<<"PO SBC";





    //zapisywanie naglowka do nowego pliku: identyfikator, wymiary: rozmiar wektora/tablicy,



    qDebug()<<"vec_compressed.size="<<vec_compressed.size();
    if(compression==1)
    {
        vec_compressed=RLE_c::compress_RLE(vec_compressed);
    }
//    ofs.write((char*)&identifier,sizeof(uint32_t));
//    ofs.write((char*)&info.size,sizeof(ImgBaseInfo::unsigned_pair));
//    ofs.write((char*)&compression_info,sizeof(uint8_t));
    qDebug()<<"PO RLE vec_compressed.size="<<vec_compressed.size();
    AAJWHEADER header;

    uint8_t buffer[4]={'A','A','J','W'};
    uint32_t identifier=(uint32_t)buffer[0] << 24 |(uint32_t)buffer[1] << 16 |(uint32_t)buffer[2] << 8  |(uint32_t)buffer[3];
    uint32_t vec_size=vec_compressed.size();

    header.FIdentifier=identifier;
    header.FSize.x=info.size.x;
    header.FSize.y=info.size.y;
    header.FDataSize=vec_size;
    header.FCompression=compression; //chosen compression val

    qDebug() <<"sizeof(header)"<<sizeof(header);
    qDebug() <<"header.FSize.x=info.size.x;"<<header.FSize.x;
    qDebug() <<"header.FSize.y=info.size.y"<<header.FSize.y;
    ofs.write((char*)&header,sizeof(header));
   // ofs.write((char*)&vec_size,sizeof(uint32_t));


    //ofs.write((char*)SBC.compressedData.data(),sizeof(vec_size* sizeof(uint8_t)));

    qDebug()<<"PO WRITE";



    //zapisywanie danych do pliku do nowego pliku -
    for(std::vector<uint8_t>::iterator it = vec_compressed.begin(); it != vec_compressed.end(); ++it)
    {
        /* std::cout << *it; ... */
        uint8_t x=*it;
        // qDebug()<<x;
        //x=x>>1;
        // qDebug()<<x;
        ofs.write((char*)&x,sizeof(uint8_t));
        //ofs2<<(int)x<<"\n";

    }


    ofs.close();

}

void MainWindow::reconvert(std::string name)
{
    std::ifstream ifs(name, std::ios::binary);
    //std::ofstream ofs(name+".kek");

    //zczytanie naglowka
    AAJWHEADER header;



    ifs.read (reinterpret_cast<char *>(&header), sizeof(header));
    //ifs.read (reinterpret_cast<char *>(&vec_size), sizeof(vec_size));

    //if(header.FIdentifier!="insert something")


    unsigned_pair size;
    size.x=header.FSize.x;
    size.y=header.FSize.y;
    uint32_t vec_size=header.FDataSize;
    uint8_t compression=header.FCompression;





    qDebug()<<"x="<<size.x<<" y="<<size.y;
    qDebug()<<"vec size="<<vec_size;
    //uint8_t *arr=new uint8_t[size.x*size.y*4];
    std::vector<uint8_t> vec_compressed;
    std::vector<uint8_t> myData;

    //myData.resize(ssize);

    SevenBitComp SBC;
    //    ifs.read((char*)myData.data(), size.x*size.y *3* sizeof(uint8_t));
    qDebug()<<"preread "<<vec_size*sizeof(uint8_t);

    vec_compressed.resize(vec_size*sizeof(uint8_t));
    ifs.read((char*)vec_compressed.data(), vec_size* sizeof(uint8_t)); //sizeof(vec_size* sizeof(uint8_t))
    qDebug()<<vec_compressed.size();


    if(compression==1)
    {
         qDebug()<<"compression RLE";
        vec_compressed=RLE_c::decompress_RLE(vec_compressed);
    }


    SBC.decompress(myData,vec_compressed);
    //myData=vec_compressed;
    vec_compressed.clear();
    vec_compressed.resize(1);
    qDebug()<<"AFTER DECOMPRESS"<<endl;


    std::ofstream ofs2(name+".txt",std::ios::trunc);

    for(unsigned int i=0;i<myData.size();i++)
        ofs2<<(int)myData[i]<<"\n";

    std::string str=name+".bmp";
    qDebug()<<"mydata size="<<myData.size();

    myData=Vec_Extr::PackVectorTo32Bit(myData,size.x,size.y,Vec_Extr::RGB);

    qDebug()<<"mydata.size po pak="<<myData.size();
    qDebug()<<Vec_Extr::SaveTo24BMP(str.c_str(),myData,size.x,size.y);
    //qDebug()<<SaveImage(str.c_str(),&myData,size.x,size.y);


    ifs.close();
    //ofs.close();

}




