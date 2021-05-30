import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'App Portão',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: Home(title: 'App Portão'),
    );
  }
}

class Home extends StatefulWidget {
  Home({Key? key, required this.title}) : super(key: key);

  final String title;

  @override
  _HomeState createState() => _HomeState();
}

class _HomeState extends State<Home> {

  Future<void> acionarPortao() async {
    http.get(Uri.parse('http://192.168.2.175/?abrir=SENHA-PARA-ABRIR'));
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            ElevatedButton(
              onPressed: acionarPortao,
              child: Text("Acionar o Portão"),
            ),
          ],
        ),
      ),
    );
  }
}
