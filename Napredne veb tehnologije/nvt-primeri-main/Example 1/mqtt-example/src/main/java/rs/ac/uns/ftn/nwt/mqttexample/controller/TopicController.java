package rs.ac.uns.ftn.nwt.mqttexample.controller;

import jakarta.validation.Valid;
import org.eclipse.paho.mqttv5.client.IMqttClient;
import org.eclipse.paho.mqttv5.common.MqttException;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;
import rs.ac.uns.ftn.nwt.mqttexample.dto.TopicSubscription;
import rs.ac.uns.ftn.nwt.mqttexample.model.Measurement;
import rs.ac.uns.ftn.nwt.mqttexample.service.MeasurementService;

import java.util.List;

@RestController
@RequestMapping(value = "topics")
public class TopicController {

    private final IMqttClient mqttClient;
    private final MeasurementService measurementService;

    public TopicController(IMqttClient mqttClient, MeasurementService measurementService) {
        this.mqttClient = mqttClient;
        this.measurementService = measurementService;
    }

    @RequestMapping(method = RequestMethod.GET)
    public ResponseEntity<List<Measurement>> getAll(String topic) {
        return new ResponseEntity<>(this.measurementService.findByTopic(topic), HttpStatus.OK);
    }

    @RequestMapping(method = RequestMethod.POST)
    public ResponseEntity<Object> subscribe(@Valid @RequestBody TopicSubscription topic) throws MqttException {
        this.mqttClient.subscribe(topic.getTopic(), 2);
        return new ResponseEntity<>(HttpStatus.OK);
    }
}
